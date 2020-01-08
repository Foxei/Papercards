#ifndef PAPER_CARDS_FIELD_H
#define PAPER_CARDS_FIELD_H

#include <QObject>
#include <QString>
#include <QFont>
#include <QJsonObject>
#include <QDebug>

/**
 * @brief A field represent a block of text with some properties.
 * @details Each block of text on a card is represented as a field.
 */
class Field : public QObject {
  Q_OBJECT
  Q_PROPERTY(FieldType type_ READ type WRITE setType NOTIFY typeChanged)
  Q_PROPERTY(QString name_ READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString text_ READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(QFont font_ READ font WRITE setFont NOTIFY fontChanged)

 public:
  /**
   * @brief Determines the type of text that is stored.
   */
  enum class FieldType{
    LINE, ///< A single or multiple lines of text no styles of lists
    BLOCK, ///< A block of text containing listings and styles
    UNKNOWN ///< Type that is used if an unknown string is defined in the config
  };

 private:
  QString  name_; ///< Name of the field
  FieldType  type_; ///< Type of the field
  QString text_; ///< Content of this field
  QFont font_; ///< Font of this field

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
  FieldType type();

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
   * @brief Will parse all values from a json config.
   * @param json_node Node to parse from.
   * @return True if nothing went wrong.
   */
  bool parseConfig(const QJsonObject &json_node);


 public slots:

  /**
   * @brief Setter for the field type.
   * @param type New field type.
   */
  void setName(const QString& name);

  /**
   * @brief Setter for the field type.
   * @param type New field type.
   */
  void setType(const FieldType& type);

  /**
   * @brief Setter for the field content.
   * @param text New field content.
   */
  void setText(const QString& text);

  /**
   * @brief Setter for the field font.
   * @param font New field font.
   */
  void setFont(const QFont& font);

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
  void typeChanged(FieldType);

  /**
   * @brief Emitted if the field content changes.
   */
  void textChanged(QString);

  /**
   * @brief Emitted if the field font is changed.
   */
  void fontChanged(QFont);

};

#endif //PAPER_CARDS_FIELD_H
