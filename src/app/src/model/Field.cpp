#include "Field.h"
#include "src/model/utility/JsonParser.h"

#include <QStringBuilder>

QString Field::name() {
  return this->name_;
}

Field::FieldType Field::type() {
  return this->type_;
}

QString Field::text() {
  return this->text_;
}

QFont Field::font() {
  return this->font_;
}

Field::FieldType stringToType(const QString &type_string){
  if(type_string == "block"){
    return Field::FieldType::BLOCK;
  }else if(type_string == "line"){
    return Field::FieldType::LINE;
  }
  return Field::FieldType::UNKNOWN;
}

QString typeToString(const Field::FieldType &type){
  switch (type){
    case Field::FieldType ::LINE: return "line";
    case Field::FieldType ::BLOCK: return "block";
    default: return "unknown";
  }
}

bool Field::parseConfig(const QJsonObject &json_node) {
  // Load required fields
  if(!json_node.contains("name")){
    qWarning("Parsing field from json node has failed. Missing field: \"name\"");
    return false;
  }
  if(!json_node["name"].isString()){
    qWarning("Parsing field from json node has failed. Node is not a string: \"name\"");
    return false;
  }
  QString name = json_node["name"].toString();
  setName(name);

  if(!json_node.contains("type")){
    qWarning("Parsing field from json node has failed. Missing field: \"type\"");
    return false;
  }
  if(!json_node["type"].isString()){
    qWarning("Parsing field from json node has failed. Node is not a string: \"type\"");
    return false;
  }
  Field::FieldType type = stringToType(json_node["type"].toString());
  setType(type);

  if(!json_node.contains("font")){
    qWarning("Parsing field from json node has failed. Missing field: \"font\"");
    return false;
  }
  if(!json_node["font"].isObject()){
    qWarning("Parsing field from json node has failed. Node is not an object: \"font\"");
    return false;
  }
  QFont font = JsonParser::toFont(json_node["font"].toObject());
  setFont(font);

  // Load not required fields
  QString text = json_node["text"].toString("");
  setText(text);

  return true;
}

void Field::setName(const QString &name) {
  // check if really something has changed.
  if(this->name_ == name) return;

  this->name_ = name;
  emit nameChanged(this->name_);
}

void Field::setType(const FieldType &type) {
  // check if really something has changed.
  if(this->type_ == type) return;

  this->type_ = type;
  emit typeChanged(this->type_);
}

void Field::setText(const QString &text) {
  // check if really something has changed.
  if(this->text_ == text) return;

  this->text_ = text;
  emit textChanged(this->text_);
}

void Field::setFont(const QFont &font) {
  // check if really something has changed.
  if(this->font_ == font) return;

  this->font_ = font;
  emit fontChanged(this->font_);
}

QString Field::toString() {
  QString message;
  message += "[Field] {";
  message += "\n Name: " + this->name_;
  message += "\n Type: " + typeToString(this->type_);
  message += "\n Font: " + this->font_.toString();
  message += "\n Text: " + this->text_;
message += "\n}";
  return message;
}
