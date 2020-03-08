#ifndef PAPER_CARDS_QML_CARD_H
#define PAPER_CARDS_QML_CARD_H

#include <QObject>
#include <QRectF>

class Card : public QObject {
 public:
  enum CardOrientation {
    Landscape,
    Portrait
  };
 private:
  // @formatter:off
  Q_OBJECT
  Q_PROPERTY(QRectF card_size READ cardSize WRITE setCardSize NOTIFY cardsSizeChanged)
  Q_PROPERTY(CardOrientation card_orientation_ READ cardOrientation WRITE setCardOrientation NOTIFY cardsOrientationChanged)
  Q_ENUM(CardOrientation)
  // @formatter:on

 private:
  QRectF card_size_;
  CardOrientation card_orientation_;


 public:
  explicit Card(QObject *parent = nullptr);

  bool parse(const QJsonObject &json_node);
  bool write(QJsonObject &json_node);

  const QRectF &cardSize();
  const CardOrientation &cardOrientation();

 public slots:
  void setCardSize(QRectF card_size);
  void setCardOrientation(CardOrientation card_orientation);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
 signals:
  void cardsSizeChanged();
  void cardsOrientationChanged();
#pragma clang diagnostic pop
};

#endif //PAPER_CARDS_QML_CARD_H
