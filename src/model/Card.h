#ifndef PAPER_CARDS_QML_CARD_H
#define PAPER_CARDS_QML_CARD_H

#include <QObject>
#include <QRectF>
#include <QtQuick/QQuickTextDocument>

class Card : public QObject {
 public:
  enum CardOrientation {
    Landscape,
    Portrait
  };
  Q_ENUM(CardOrientation)
  enum CardField {
    Question,
    Answer
  };
  Q_ENUM(CardField)
 private:
  // @formatter:off
  Q_OBJECT
  Q_PROPERTY(QTextDocument *document READ document WRITE setDocument NOTIFY documentChanged)

  Q_PROPERTY(QRectF card_size READ cardSize WRITE setCardSize NOTIFY cardsSizeChanged)
  Q_PROPERTY(CardOrientation card_orientation READ cardOrientation WRITE setCardOrientation NOTIFY cardsOrientationChanged)
  Q_PROPERTY(QString card_question_text READ cardQuestionText WRITE setCardQuestionText NOTIFY cardQuestionTextChanged)
  Q_PROPERTY(QString card_answer_text READ cardAnswerText WRITE setCardAnswerText NOTIFY cardAnswerTextChanged)
  // @formatter:on

 private:
  QRectF card_size_;
  CardOrientation card_orientation_;
  QString card_question_text_;
  QString card_answer_text_;
  QTextDocument *document_;

 public:
  explicit Card(QObject *parent = nullptr);

  bool parse(const QJsonObject &json_node);
  bool write(QJsonObject &json_node);

  const QRectF &cardSize();
  const CardOrientation &cardOrientation();
  const QString &cardQuestionText();
  const QString &cardAnswerText();
  const QString &text(CardField field);
  QTextDocument *document() const;

 public slots:
  void setCardSize(QRectF card_size);
  void setCardOrientation(CardOrientation card_orientation);
  void setCardQuestionText(QString card_question_text);
  void setCardAnswerText(QString card_answer_text);
  void updateText(const QString &text, CardField field);
  void setDocument(QTextDocument *document);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
 signals:
  void cardsSizeChanged();
  void cardsOrientationChanged();
  void cardQuestionTextChanged();
  void cardAnswerTextChanged();
  void documentChanged();

#pragma clang diagnostic pop
};

#endif //PAPER_CARDS_QML_CARD_H
