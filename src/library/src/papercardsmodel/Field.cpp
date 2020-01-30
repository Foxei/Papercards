#include "papercardsmodel/Field.h"
#include "utility/JsonParser.h"

#include <QStringBuilder>
#include <QJsonValue>

QString Field::name() {
  return this->name_;
}

Field::Type Field::type() {
  return this->type_;
}

QString Field::text() {
  return this->text_;
}

QFont Field::font() {
  return this->font_;
}

QImage Field::image() {
  return this->image_;
}

Field::Type stringToType(const QString &type_string) {
  if (type_string == "block") {
    return Field::Type::BLOCK;
  } else if (type_string == "line") {
    return Field::Type::LINE;
  } else if (type_string == "media") {
    return Field::Type::MEDIA;
  }
  return Field::Type::UNKNOWN;
}

QString typeToString(const Field::Type &type) {
  switch (type) {
    case Field::Type::LINE: return "line";
    case Field::Type::BLOCK: return "block";
    case Field::Type::MEDIA: return "media";
    default: return "unknown";
  }
}

bool Field::parse(const QJsonObject &json_node) {
  // Load required fields
  if (!json_node.contains("name")) {
    qWarning("Parsing field from json node has failed. Missing field: \"name\"");
    return false;
  }
  if (!json_node["name"].isString()) {
    qWarning("Parsing field from json node has failed. Node is not a string: \"name\"");
    return false;
  }
  QString name = json_node["name"].toString();
  setName(name);

  if (!json_node.contains("type")) {
    qWarning("Parsing field from json node has failed. Missing field: \"type\"");
    return false;
  }
  if (!json_node["type"].isString()) {
    qWarning("Parsing field from json node has failed. Node is not a string: \"type\"");
    return false;
  }
  Field::Type type = stringToType(json_node["type"].toString());
  setType(type);

  if (!json_node.contains("font")) {
    qWarning("Parsing field from json node has failed. Missing field: \"font\"");
    return false;
  }
  if (!json_node["font"].isObject()) {
    qWarning("Parsing field from json node has failed. Node is not an object: \"font\"");
    return false;
  }
  QFont font = JsonParser::toFont(json_node["font"].toObject());
  setFont(font);

  // Load not required fields
  QString text = json_node["text"].toString("");
  setText(text);

  QImage image = JsonParser::toImage(json_node["image"]);
  setImage(image);

  return true;
}

bool Field::write(QJsonObject &json_node) {
  json_node.insert("name", name());
  json_node.insert("type", typeToString(type()));
  json_node.insert("text", text());
  json_node.insert("image", JsonParser::imageToJson(image()));

  QJsonObject font_node = JsonParser::fontToJson(font());
  json_node.insert("font", font_node);

  return true;
}

void Field::setName(const QString &name) {
  // check if really something has changed.
  if (this->name_ == name) return;

  this->name_ = name;
  emit nameChanged(this->name_);
}

void Field::setType(const Type &type) {
  // check if really something has changed.
  if (this->type_ == type) return;

  this->type_ = type;
  emit typeChanged(this->type_);
}

void Field::setText(const QString &text) {
  // check if really something has changed.
  if (this->text_ == text) return;

  this->text_ = text;
  emit textChanged(this->text_);
}

void Field::setFont(const QFont &font) {
  // check if really something has changed.
  if (this->font_ == font) return;

  this->font_ = font;
  emit fontChanged(this->font_);
}

void Field::setImage(const QImage &image) {
  // check if really something has changed.
  if (this->image_ == image) return;

  this->image_ = image;
  emit imageChanged(this->image_);
}

QString Field::toString() {
  QString message;
  message += "[Field] {";
  message += "\n Name: " + this->name_;
  message += "\n Type: " + typeToString(this->type_);
  message += "\n Font: " + this->font_.toString();
  message += "\n Text: " + this->text_;
  message += "\n Image: " + QString(this->image_.isNull());
  message += "\n}";
  return message;
}
