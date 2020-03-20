#include "DocumentHandler.h"

#include <QFile>
#include <QFileInfo>
#include <QFileSelector>
#include <QQmlFile>
#include <QQmlFileSelector>
#include <QQuickTextDocument>
#include <QTextCharFormat>
#include <QTextCodec>
#include <QTextBlock>
#include <QTextList>
#include <QTextDocument>
#include <QDebug>

DocumentHandler::DocumentHandler(QObject *parent)
  : QObject(parent), m_document(nullptr), m_cursorPosition(-1), m_selectionStart(0), m_selectionEnd(0) {
}

QQuickTextDocument *DocumentHandler::document() const {
  return m_document;
}

void DocumentHandler::setDocument(QQuickTextDocument *document) {
  if (document == m_document)
    return;

  if (m_document)
    m_document->textDocument()->disconnect(this);
  m_document = document;
  if (m_document) {
    connect(m_document->textDocument(), &QTextDocument::modificationChanged, this, &DocumentHandler::modifiedChanged);
  }
  emit documentChanged();
}

int DocumentHandler::cursorPosition() const {
  return m_cursorPosition;
}

void DocumentHandler::setCursorPosition(int position) {
  if (position == m_cursorPosition)
    return;

  m_cursorPosition = position;
  reset();
  emit cursorPositionChanged();
}

int DocumentHandler::selectionStart() const {
  return m_selectionStart;
}

void DocumentHandler::setSelectionStart(int position) {
  if (position == m_selectionStart)
    return;

  m_selectionStart = position;
  emit selectionStartChanged();
}

int DocumentHandler::selectionEnd() const {
  return m_selectionEnd;
}

void DocumentHandler::setSelectionEnd(int position) {
  if (position == m_selectionEnd)
    return;

  m_selectionEnd = position;
  emit selectionEndChanged();
}

QString DocumentHandler::fontFamily() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return QString();
  QTextCharFormat format = cursor.charFormat();
  return format.font().family();
}

void DocumentHandler::setFontFamily(const QString &family) {
  QTextCharFormat format;
  format.setFontFamily(family);
  mergeFormatOnWordOrSelection(format);
  emit fontFamilyChanged();
}

QColor DocumentHandler::textColor() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return QColor(Qt::black);
  QTextCharFormat format = cursor.charFormat();
  return format.foreground().color();
}

void DocumentHandler::setTextColor(const QColor &color) {
  QTextCharFormat format;
  format.setForeground(QBrush(color));
  mergeFormatOnWordOrSelection(format);
  emit textColorChanged();
}

Qt::Alignment DocumentHandler::alignment() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return Qt::AlignLeft;
  return textCursor().blockFormat().alignment();
}

void DocumentHandler::setAlignment(Qt::Alignment alignment) {
  QTextBlockFormat format;
  format.setAlignment(alignment);
  QTextCursor cursor = textCursor();
  cursor.mergeBlockFormat(format);
  emit alignmentChanged();
}

bool DocumentHandler::bold() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return false;
  return textCursor().charFormat().fontWeight() == QFont::Bold;
}

void DocumentHandler::setBold(bool bold) {
  QTextCharFormat format;
  format.setFontWeight(bold ? QFont::Bold : QFont::Normal);
  mergeFormatOnWordOrSelection(format);
  emit boldChanged();
}

bool DocumentHandler::italic() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return false;
  return textCursor().charFormat().fontItalic();
}

void DocumentHandler::setItalic(bool italic) {
  QTextCharFormat format;
  format.setFontItalic(italic);
  mergeFormatOnWordOrSelection(format);
  emit italicChanged();
}

bool DocumentHandler::underline() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return false;
  return textCursor().charFormat().fontUnderline();
}

void DocumentHandler::setUnderline(bool underline) {
  QTextCharFormat format;
  format.setFontUnderline(underline);
  mergeFormatOnWordOrSelection(format);
  emit underlineChanged();
}

bool DocumentHandler::bulletList() const {
  return (textCursor().block().textList() != nullptr);
}

void DocumentHandler::setBulletList(bool bullet_list) {
  if (bullet_list) {
    // Activate list
    textCursor().createList(QTextListFormat::ListDisc);
  } else {
    // Deactivate list
    if (textCursor().block().textList() != nullptr) {
      // List found
      // Reindent text to the left
      QTextListFormat listFormat;
      listFormat = textCursor().block().textList()->format();
      listFormat.setIndent(0);
      textCursor().block().textList()->setFormat(listFormat);
      // Clear list
      auto list = textCursor().block().textList();
      for (int i = list->count() - 1; i >= 0; i--) {
        list->removeItem(i);
      }
    }
  }
  emit bulletListChanged();
}

int DocumentHandler::fontSize() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return 0;
  QTextCharFormat format = cursor.charFormat();
  return format.font().pointSize();
}

void DocumentHandler::setFontSize(int size) {
  if (size <= 0)
    return;

  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return;

  if (!cursor.hasSelection())
    cursor.select(QTextCursor::WordUnderCursor);

  if (cursor.charFormat().property(QTextFormat::FontPointSize).toInt() == size)
    return;

  QTextCharFormat format;
  format.setFontPointSize(size);
  mergeFormatOnWordOrSelection(format);
  emit fontSizeChanged();
}

QString DocumentHandler::fileName() const {
  const QString filePath = QQmlFile::urlToLocalFileOrQrc(m_fileUrl);
  const QString fileName = QFileInfo(filePath).fileName();
  if (fileName.isEmpty())
    return QStringLiteral("untitled.txt");
  return fileName;
}

QString DocumentHandler::fileType() const {
  return QFileInfo(fileName()).suffix();
}

QUrl DocumentHandler::fileUrl() const {
  return m_fileUrl;
}

void DocumentHandler::increaseIndentation() {
  QTextListFormat listFormat;
  listFormat.setIndent(1);
  if (textCursor().block().textList() != nullptr) {
    listFormat = textCursor().block().textList()->format();
    listFormat.setIndent(listFormat.indent() + 1);
  }
  textCursor().createList(listFormat);
  textCursor().setPosition(0);
}

void DocumentHandler::decreaseIndentation() {
  if (textCursor().block().textList() != nullptr) {
    // List found
    // Increase indentation
    QTextListFormat listFormat;
    listFormat = textCursor().block().textList()->format();
    listFormat.setIndent(listFormat.indent() - 1);
    textCursor().createList(listFormat);
    if (listFormat.indent() < 1) {
      auto list = textCursor().block().textList();
      for (int i = list->count() - 1; i >= 0; i--) {
        list->removeItem(i);
      }
    }
  }
}

void DocumentHandler::formatText() {
  QTextCharFormat format;
  format.setFontWeight(QFont::Bold);
  QTextDocument *doc = textDocument();
  QTextCursor cursor = QTextCursor(doc);
  cursor.select(QTextCursor::WordUnderCursor);
  cursor.mergeCharFormat(format);
}

void DocumentHandler::load(const QUrl &fileUrl) {
  document()->textDocument()->setHtml("<html>This is an test.</html>");
  //emit loaded("<html>This is an test.</html>");
}

void DocumentHandler::saveAs(const QUrl &fileUrl) {
  QTextDocument *doc = textDocument();
  if (!doc)
    return;

  const QString filePath = fileUrl.toLocalFile();
  const bool isHtml = QFileInfo(filePath).suffix().contains(QLatin1String("htm"));
  QFile file(filePath);
  if (!file.open(QFile::WriteOnly | QFile::Truncate | (isHtml ? QFile::NotOpen : QFile::Text))) {
    emit error(tr("Cannot save: ") + file.errorString());
    return;
  }
  file.write((isHtml ? doc->toHtml() : doc->toPlainText()).toUtf8());
  file.close();

  if (fileUrl == m_fileUrl)
    return;

  m_fileUrl = fileUrl;
  emit fileUrlChanged();
}

void DocumentHandler::reset() {
  emit fontFamilyChanged();
  emit alignmentChanged();
  emit boldChanged();
  emit italicChanged();
  emit underlineChanged();
  emit fontSizeChanged();
  emit textColorChanged();
}

QTextCursor DocumentHandler::textCursor() const {
  QTextDocument *doc = textDocument();
  if (!doc)
    return QTextCursor();

  QTextCursor cursor = QTextCursor(doc);
  if (m_selectionStart != m_selectionEnd) {
    cursor.setPosition(m_selectionStart);
    cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
  } else {
    cursor.setPosition(m_cursorPosition);
  }
  return cursor;
}

QTextDocument *DocumentHandler::textDocument() const {
  if (!m_document)
    return nullptr;

  return m_document->textDocument();
}

void DocumentHandler::mergeFormatOnWordOrSelection(const QTextCharFormat &format) {
  QTextCursor cursor = textCursor();
  if (!cursor.hasSelection())
    cursor.select(QTextCursor::WordUnderCursor);
  cursor.mergeCharFormat(format);
}

bool DocumentHandler::modified() const {
  return m_document && m_document->textDocument()->isModified();
}

void DocumentHandler::setModified(bool m) {
  if (m_document)
    m_document->textDocument()->setModified(m);
}
