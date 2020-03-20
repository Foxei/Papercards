#ifndef DOCUMENT_HANDLER_H
#define DOCUMENT_HANDLER_H

#include <QFont>
#include <QObject>
#include <QTextCursor>
#include <QUrl>

#include "model/Card.h"

QT_BEGIN_NAMESPACE
class QTextDocument;
class QQuickTextDocument;
QT_END_NAMESPACE

class DocumentHandler : public QObject {
  //@formatter:off
  Q_OBJECT

  // Text document that handles the user inputs
  Q_PROPERTY(QQuickTextDocument *document READ document WRITE setDocument NOTIFY documentChanged)
  // Check cursor location
  Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)
  Q_PROPERTY(int selectionStart READ selectionStart WRITE setSelectionStart NOTIFY selectionStartChanged)
  Q_PROPERTY(int selectionEnd READ selectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged)

  // User inputs for text modification
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
  Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)
  Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)
  Q_PROPERTY(bool bold READ bold WRITE setBold NOTIFY boldChanged)
  Q_PROPERTY(bool italic READ italic WRITE setItalic NOTIFY italicChanged)
  Q_PROPERTY(bool underline READ underline WRITE setUnderline NOTIFY underlineChanged)
  Q_PROPERTY(bool bulletList READ bulletList WRITE setBulletList NOTIFY bulletListChanged)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)

  // Card that should be updated
  Q_PROPERTY(Card* card READ card WRITE setCard NOTIFY cardChanged)
  Q_PROPERTY(Card::CardField cardField READ cardField WRITE setCardField NOTIFY cardFieldChanged)
  //@formatter:on
 public:
  explicit DocumentHandler(QObject *parent = nullptr);

  QQuickTextDocument *document() const;
  void setDocument(QQuickTextDocument *document);

  int cursorPosition() const;
  void setCursorPosition(int position);

  int selectionStart() const;
  void setSelectionStart(int position);

  int selectionEnd() const;
  void setSelectionEnd(int position);

  QColor textColor() const;
  void setTextColor(const QColor &color);

  QColor highlightColor() const;
  void setHighlightColor(const QColor &color);

  Qt::Alignment alignment() const;
  void setAlignment(Qt::Alignment alignment);

  bool bold() const;
  void setBold(bool bold);

  bool italic() const;
  void setItalic(bool italic);

  bool underline() const;
  void setUnderline(bool underline);

  bool bulletList() const;
  void setBulletList(bool bullet_list);

  int fontSize() const;
  void setFontSize(int size);

  Card *card() const;
  void setCard(Card *card);

  Card::CardField cardField() const;
  void setCardField(Card::CardField card_field);

  Q_INVOKABLE void increaseIndentation();
  Q_INVOKABLE void decreaseIndentation();
  Q_INVOKABLE void resetHighlightColor();
  Q_INVOKABLE void resetTextColor();

 public Q_SLOTS:
  void load();
  void updateCard();

 Q_SIGNALS:
  void documentChanged();
  void cursorPositionChanged();
  void selectionStartChanged();
  void selectionEndChanged();

  void textColorChanged();
  void highlightColorChanged();
  void alignmentChanged();

  void boldChanged();
  void italicChanged();
  void underlineChanged();
  void bulletListChanged();

  void fontSizeChanged();

  void loaded();
  void error(const QString &message);

  void cardChanged();
  void cardFieldChanged();

 private:
  void reset();
  QTextCursor textCursor() const;
  QTextDocument *textDocument() const;
  void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

  QQuickTextDocument *m_document;

  int m_cursorPosition;
  int m_selectionStart;
  int m_selectionEnd;
  Card *card_ = nullptr;
  Card::CardField card_field_;

  QFont m_font;
  QUrl m_fileUrl;
};

#endif // DOCUMENT_HANDLER_H
