#ifndef PAPER_CARDS_CARD_H
#define PAPER_CARDS_CARD_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QPageLayout>
#include <QPageSize>
#include <QJsonObject>

#include "model/Field.h"

/**
 * @brief Represents a card including all it fields.oth sides are a number of fields.
 * @details A card has two sides and on b
 */
class Card : public QObject {
  //@formatter::on
 Q_OBJECT
  Q_PROPERTY(QPageLayout::Orientation card_orientation_
                 READ
                     orientation
                 WRITE
                     setOrientation
                 NOTIFY
                 orientationChanged)
  Q_PROPERTY(QPageSize card_size_
                 READ
                     size
                 WRITE
                     setSize
                 NOTIFY
                 sizeChanged)
  //@formatter:off
 public:

  /**
   * @berief Enum so separate both sides.
   * @details A card has two sides: front and back.
   */
  enum Site {
    FRONT = 0,
    BACK = 1
  };

  /**
   * @brief Enum to separate the card style.
   * @details
   * @enum TITLE_ONLY Contains only a single line edit to enter a question.
   * @enum TITLE_CONTENT Contains a title and a block of text as details explanation.
   * This may contains lists as well.
   * @enum TITLE_MEDIA Contains a title and an image as detail.
   * @enum UNKNOWN This is to handle parser errors.
   */
  enum Style {
    TITLE_ONLY,
    TITLE_CONTENT,
    TITLE_MEDIA,
    UNKNOWN
  };

 private:
  QPageSize card_size_; ///< Print size of the card.
  QPageLayout::Orientation card_orientation_; ///< Print orientation of the card
  Style styles_[2]; ///< Styles of the two card sites.
  QVector<Field *> card_fields_[2]; ///< Field that are editable on a card.

  /**
   * @brief Parse a single card definition.
   * @details Used to store both sites of a card.
   * @param json_node Node to parse from.
   * @param site Site that should be parsed.
   * @return True if nothing went wrong, false otherwise.
   */
  bool parseCard(const QJsonObject &json_node, Card::Site site);

  /**
   * @brief Will write a single card definition to a json.
   * @details Used to parse both sides of the card.
   * @param json_node Node to write to.
   * @param site Site that should be written.
   * @return True if nothing went wrong, false otherwise.
   */
  bool writeCard(QJsonObject &json_node, Card::Site site);

 public:

  /**
   * @brief Will parse a card from a json config.
   * @param json_node Json node to parse.
   * @return True if nothing went wrong while parsing.
   */
  bool parse(const QJsonObject &json_node);

  /**
   * @brief Will write a card to a json config.
   * @param json_node Json node to write.
   * @return True if nothing went wrong while writing.
   */
  bool write(QJsonObject &json_node);

  /**
   * @brief Sets the style of a card.
   * @param site Site of card.
   * @param style Style of card site.
   */
  Card::Style getStyle(Card::Site site);

  /**
   * @brief Access fields on a card.
   * @param name Name of the field.
   * @param site Site of the card.
   * @return Field pointer or, nullptr if not found.
   */
  Field *getField(const QString &name, Site site);

  /**
   * @brief Getter for the card orientation.
   * @return Card orientation
   */
  QPageLayout::Orientation orientation();

  /**
   * @brief Getter for the card size.
   * @return Card size
   */
  QPageSize size();

  /**
   * @brief Converts key elements to a string.
   * @return String of contents.
   */
  QString toString();

 public slots:

  /**
   * @brief Sets the style of a card.
   * @param site Site of card.
   * @param style Style of card site.
   */
  void setStyle(Card::Site site, Card::Style style);

  /**
   * @brief Set orientation of the card.
   * @param orientation New card orientation.
   */
  void setOrientation(QPageLayout::Orientation orientation);

  /**
   * @brief Setter for the card size.
   * @param size New page size.
   */
  void setSize(const QPageSize& size);

 signals:

  /**
   * @brief Will be emitted if the card style of one site is changed.
   * @param site Site were the style was changed.
   * @param style Style that is now used.
   */
  void styleChanged(Card::Site site, Card::Style style);

  /**
   * @brief Will be emitted if the card orientation has changed.
   * @param orientation Orientation that is now used.
   */
  void orientationChanged(QPageLayout::Orientation orientation);

  /**
   * @brief Will be emitted if the card size has changed.
   * @param size Size that is now used.
   */
  void sizeChanged(QPageSize size);
};

#endif //PAPER_CARDS_CARD_H
