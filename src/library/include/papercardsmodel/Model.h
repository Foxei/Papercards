/**
 * @file Model.h
 * @author Simon Schäfer
 * @date 31.01.20
 */

#ifndef PAPER_CARDS_MODEL_H
#define PAPER_CARDS_MODEL_H

#include <QObject>

#include "Card.h"

/**
 * @brief Represents a model that fully supports storing loading and managing the cards that are created in the
 * papercards application.
 * @details This class is the only direct communication that is possible to the model (MVC).
 */
class Model : QObject {
 Q_OBJECT

 private:

  std::shared_ptr<Card> default_card; ///< Stores the default card.

  /**
   * @brief Prevents the instantiation of a model (singleton).
   */
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
