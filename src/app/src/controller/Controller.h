#ifndef PAPER_CARDS_CONTROLLER_H
#define PAPER_CARDS_CONTROLLER_H

#include <QVariant>

#include <papercardsmodel/Card.h>

class Controller : public QObject {
 Q_OBJECT
 private:

  Card *current_displayed_card = nullptr;

  Controller() = default;

  void showSite(Card::Site site, Card *card);

 public:

  static Controller *instance() {
    static Controller controller;
    return &controller;
  }

  void init();

  void connectModelAndView();

  void free();

 public slots:

  void showCard(Card *card);

  void updateModelData(bool front, const QString &field_name, const QVariant &field_content);

 signals:

  void showCardElement(bool front, QString field_name, bool visible);

  void updateCardElement(bool front, QString field_name, QVariant field_content);

  void updateCardElementFont(bool front, QString field_name, QFont field_content);

  void updateCardSize(QSizeF card_size, QPageLayout::Orientation card_orientation);

};

#endif //PAPER_CARDS_CONTROLLER_H
