/**
 * @file Field.h
 * @author Simon Schäfer
 * @date 31.01.20
 */

#ifndef PAPER_CARDS_FIELD_H
#define PAPER_CARDS_FIELD_H

#include <QFont>
#include <QImage>

/**
 * @brief A field represent a block of text with some properties.
 * @details Each block of text on a card is represented as a field.
 */
class Field : public QObject {
  // @formatter:off
  Q_OBJECT
  Q_PROPERTY(Type type_ READ type WRITE setType NOTIFY typeChanged)
  Q_PROPERTY(QString name_ READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString text_ READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(QFont font_ READ font WRITE setFont NOTIFY fontChanged)
  Q_PROPERTY(QImage image_ READ image WRITE setImage NOTIFY imageChanged)
  // @formatter:on

 public:
  /**
   * @brief Determines the type of text that is stored.
   */
  enum class Type {
    LINE, ///< A single or multiple lines of text no styles of lists
    BLOCK, ///< A block of text containing listings and styles
    MEDIA, ///< An image as content
    UNKNOWN ///< Type that is used if an unknown string is defined in the config
  };

 private:
  QString name_; ///< Name of the field
  Type type_; ///< Type of the field
  QString text_; ///< Content of this field
  QFont font_; ///< Font of this field
  QImage image_; ///< Media of this field

 public:
  /**
   * @brief Getter for the field name.
   * @return field name.
   */
  QString name();

  /**
   * @brief Getter for the field type.
   * @return field type.
   */
  Type type();

  /**
   * @brief Getter for the content of the field.
   * @return field content.
   */
  QString text();

  /**
   * @brief Getter for the font of the field.
   * @return field font.
   */
  QFont font();

  /**
   * @brief Getter for the media of the field.
   * @return field media.
   */
  QImage image();

  /**
   * @brief Will parse all values from a json config.
   * @param json_node Node to parse from.
   * @return True if nothing went wrong.
   */
  bool parse(const QJsonObject &json_node);

  /**
   * @brief Will write all values to a json config.
   * @param json_node Node to write to.
   * @return True if nothing went wrong.
   */
  bool write(QJsonObject &json_node);

 public slots:

  /**
   * @brief Setter for the field type.
   * @param type New field type.
   */
  void setName(const QString &name);

  /**
   * @brief Setter for the field type.
   * @param type New field type.
   */
  void setType(const Type &type);

  /**
   * @brief Setter for the field content.
   * @param text New field content.
   */
  void setText(const QString &text);

  /**
   * @brief Setter for the field font.
   * @param font New field font.
   */
  void setFont(const QFont &font);

  /**
   * @brief Setter for the field media.
   * @param font New field media.
   */
  void setImage(const QImage &image);

  /**
   * @brief Converts key elements to a string.
   * @return String of contents.
   */
  QString toString();

 signals:

  /**
   * @brief Emitted if the field name changed.
   */
  void nameChanged(QString);

  /**
   * @brief Emitted if the field type changed.
   */
  void typeChanged(Type);

  /**
   * @brief Emitted if the field content changes.
   */
  void textChanged(QString);

  /**
   * @brief Emitted if the field font is changed.
   */
  void fontChanged(QFont);

  /**
   * @brief Emitted if the field font is changed.
   */
  void imageChanged(QImage);

};

#endif //PAPER_CARDS_FIELD_H
