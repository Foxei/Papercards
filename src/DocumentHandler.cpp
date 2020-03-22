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

#include "Backend.h"

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
    connect(m_document->textDocument(), &QTextDocument::contentsChanged, this, &DocumentHandler::updateCard);
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

void DocumentHandler::resetTextColor() {
  QTextCharFormat format;
  format.setForeground(QBrush());
  mergeFormatOnWordOrSelection(format);
  emit textColorChanged();
}

QColor DocumentHandler::highlightColor() const {
  QTextCursor cursor = textCursor();
  if (cursor.isNull())
    return QColor(Qt::black);
  QTextCharFormat format = cursor.charFormat();
  return format.background().color();
}

void DocumentHandler::setHighlightColor(const QColor &color) {
  QTextCharFormat format;
  format.setBackground(QBrush(color));
  mergeFormatOnWordOrSelection(format);
  emit textColorChanged();
}

void DocumentHandler::resetHighlightColor() {
  QTextCharFormat format;
  format.setBackground(QBrush());
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

void DocumentHandler::updateCard() {
  if(this->card_ && this->textDocument()){
    this->card()->updateText(this->textDocument()->toHtml(), this->card_field_);
    BackEnd::instance()->setModified(true);
  }
}

void DocumentHandler::load() {
  if(this->card_ == nullptr) return;
  document()->textDocument()->setHtml(card()->text(this->card_field_));
  BackEnd::instance()->setModified(false);
  emit loaded();
}

void DocumentHandler::reset() {
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

Card* DocumentHandler::card() const {
  return this->card_;
}

void DocumentHandler::setCard(Card *card) {
  this->card_ = card;
  emit cardChanged();
}
Card::CardField DocumentHandler::cardField() const {
  return this->card_field_;
}
void DocumentHandler::setCardField(Card::CardField card_field) {
  this->card_field_ = card_field;
  emit cardFieldChanged();
}
