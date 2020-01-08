#include "Card.h"

#include <QJsonArray>

Card::Style stringToStyle(const QString &style_string){
  if(style_string == "title_only"){
    return Card::Style ::TITLE_ONLY;
  }else if(style_string == "title_content"){
    return Card::Style ::TITLE_CONTENT;
  }
  return Card::Style ::UNKNOWN;
}

QString styleToString(const Card::Style &style){
  switch (style){
    case Card::Style ::TITLE_ONLY: return "title_only";
    case Card::Style ::TITLE_CONTENT: return "title_content";
    default: return "unknown";
  }
}

bool Card::parseCardConfig(const QJsonObject &json_node, Card::Site site){
  if (!json_node.contains("style")) {
    qWarning("Parsing card from json node has failed. Missing field: \"style\"");
    return false;
  }
  if (!json_node["style"].isString()) {
    qWarning("Parsing card from json node has failed. Node is not an String: \"style\"");
    return false;
  }
  Card::Style style = stringToStyle(json_node["style"].toString());
  setStyle(site, style);

  if (!json_node.contains("fields")) {
    qWarning("Parsing card from json node has failed. Missing field: \"fields\"");
    return false;
  }
  if (!json_node["fields"].isArray()) {
    qWarning("Parsing card from json node has failed. Node is not an array: \"fields\"");
    return false;
  }

  QJsonArray field_array_node = json_node["fields"].toArray();
  card_fields_[site].clear();
  for (auto field_array_iterator = field_array_node.begin(); field_array_iterator != field_array_node.end();
       field_array_iterator++) {
    QJsonObject field_node = field_array_iterator->toObject();
    auto *field = new Field;
    bool results = field->parseConfig(field_node);
    if (!results) {
      qWarning("Parsing card from json node failed partially. Error while parsing field, current field will be skipped.");
      continue;
    }
    card_fields_[site].push_back(field);
  }
}

bool Card::parseConfig(const QJsonObject &json_node) {

  if (!json_node.contains("front")) {
    qWarning("Parsing card from json node has failed. Missing field: \"front\"");
    return false;
  }
  if (!json_node["front"].isObject()) {
    qWarning("Parsing card from json node has failed. Node is not an object: \"front\"");
    return false;
  }
  QJsonObject front_node = json_node["front"].toObject();
  parseCardConfig(front_node, Card::Site::FRONT);

  if (!json_node.contains("back")) {
    qWarning("Parsing card from json node has failed. Missing field: \"back\"");
    return false;
  }
  if (!json_node["back"].isObject()) {
    qWarning("Parsing card from json node has failed. Node is not an object: \"back\"");
    return false;
  }
  QJsonObject back_node = json_node["back"].toObject();
  parseCardConfig(back_node, Card::Site::BACK);

  return true;
}

void Card::setStyle(Card::Site site, Card::Style style) {
  // Check if really something changed
  if(this->styles_[site] == style) return;
  this->styles_[site] = style;
  emit styleChanged(site, style);
}

Field *Card::getField(const QString &name, Site site) {
  for (Field *field:card_fields_[site]) {
    if (field->name() == name) return field;
  }
  return nullptr;
}

QString Card::toString() {
  QString message;
  message += "[Card] {";
  message += "\n[Front]";
  message += "\n Number of fields: " + QString::number(card_fields_[Site::FRONT].size());
  for (auto &card_field : card_fields_[Site::FRONT]) {
    message += +"\n" + card_field->toString();
  }
  message += "\n[Back]";
  message += "\n Number of fields: " + QString::number(card_fields_[Site::BACK].size());
  for (auto &card_field : card_fields_[Site::BACK]) {
    message += +"\n" + card_field->toString();
  }
  message += "\n}";
  return message;
}