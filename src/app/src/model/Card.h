#ifndef PAPER_CARDS_CARD_H
#define PAPER_CARDS_CARD_H

#include <QObject>
#include <QVector>
#include <QJsonObject>

#include "model/Field.h"

/**
 * @brief Represents a card including all its fields.
 */
class Card : public QObject {
 Q_OBJECT
 public:

  enum Site {
    FRONT = 0,
    BACK = 1
  };

  enum Style {
    TITLE_ONLY,
    TITLE_CONTENT,
    UNKNOWN
  };

 private:
  Style styles_[2]; ///< Styles of the two card sites

  QVector<Field *> card_fields_[2]; ///< Field that are editable on a card

  bool parseCardConfig(const QJsonObject &json_node, Card::Site site);
 public:

  /**
   * @brief Will parse a card from a json config.
   * @param json_node Json node to parse.
   * @return True if nothing went wrong while parsing.
   */
  bool parseConfig(const QJsonObject &json_node);

  /**
   * @brief Sets the style of a card.
   * @param site Site of card.
   * @param style Style of card site.
   */
  void setStyle(Card::Site site, Card::Style style);

  /**
   * @brief Access fields on a card.
   * @param name Name of the field.
   * @param site Site of the card.
   * @return Field pointer or, nullptr if not found.
   */
  Field *getField(const QString &name, Site site);

  /**
   * @brief Converts key elements to a string.
   * @return String of contents.
   */
  QString toString();

  signals:

  /**
   * @brief Will be emitted if the card style of one site is changed.
   * @param site Site were the style was changed.
   * @param style Style tha is now used.
   */
  void styleChanged(Card::Site site, Card::Style style);
};

#endif //PAPER_CARDS_CARD_H
