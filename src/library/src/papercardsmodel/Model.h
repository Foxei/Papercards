#ifndef PAPER_CARDS_MODEL_H
#define PAPER_CARDS_MODEL_H

#include <QObject>

#include "Card.h"

class Model : QObject {
 Q_OBJECT

 private:

  std::shared_ptr<Card> default_card;

  Model() = default;

  bool loadDefaultCard(const QString &file_name);

  bool storeCard(const QString &file_name);

 public:

  static Model *instance() {
    static Model model;
    return &model;
  }

  void init();

  bool loadConfig();

  bool storeConfig();

  void free();

  std::weak_ptr<Card> defaultCard();

};

#endif //PAPER_CARDS_MODEL_H
