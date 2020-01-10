#include "Card.h"

#include <QJsonArray>

Card::Style stringToStyle(const QString &style_string) {
  if (style_string == "title_only") {
    return Card::Style::TITLE_ONLY;
  } else if (style_string == "title_content") {
    return Card::Style::TITLE_CONTENT;
  } else if (style_string == "title_media") {
    return Card::Style::TITLE_MEDIA;
  }
  return Card::Style::UNKNOWN;
}

QString styleToString(const Card::Style &style) {
  switch (style) {
    case Card::Style::TITLE_ONLY: return "title_only";
    case Card::Style::TITLE_CONTENT: return "title_content";
    case Card::Style::TITLE_MEDIA: return "title_media";
    default: return "unknown";
  }
}

QPageLayout::Orientation stringToOrientation(const QString &style_string) {
  if (style_string == "portrait") {
    return QPageLayout::Orientation::Portrait;
  }
  return QPageLayout::Orientation::Landscape;
}

QString orientationToString(const QPageLayout::Orientation &orientation) {
  switch (orientation) {
    case QPageLayout::Orientation::Landscape: return "landscape";
    case QPageLayout::Orientation::Portrait: return "portrait";
  }
}

QPageSize stringToSize(const QString &style_string) {
  if (style_string == "A5") {
    return QPageSize(QPageSize::A5);
  }
  return QPageSize(QPageSize::A6);
}

QString sizeToString(const QPageSize &size) {
  switch (size.id()) {
    case QPageSize::A6: return "A6";
    case QPageSize::A5: return "A5";
    default: return "unknown";
  }
}

bool Card::parseCard(const QJsonObject &json_node, Card::Site site) {
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
    bool results = field->parse(field_node);
    if (!results) {
      qWarning("Parsing card from json node failed partially. Error while parsing field, current field will be skipped.");
      continue;
    }
    card_fields_[site].push_back(field);
  }
  return true;
}

bool Card::writeCard(QJsonObject &json_node, Card::Site site) {
  json_node.insert("style", styleToString(getStyle(site)));

  QJsonArray json_array_node;
  for (auto &field_array_iterator : card_fields_[site]) {
    QJsonObject field_node;
    field_array_iterator->write(field_node);

    json_array_node.push_back(field_node);
  }
  json_node.insert("fields", json_array_node);

  return true;
}

bool Card::parse(const QJsonObject &json_node) {
  if (!json_node.contains("orientation")) {
    qWarning("Parsing card from json node has failed. Missing field: \"orientation\"");
    return false;
  }
  if (!json_node["orientation"].isString()) {
    qWarning("Parsing card from json node has failed. Node is not an String: \"orientation\"");
    return false;
  }
  QPageLayout::Orientation orientation = stringToOrientation(json_node["orientation"].toString());
  setOrientation(orientation);

  if (!json_node.contains("size")) {
    qWarning("Parsing card from json node has failed. Missing field: \"size\"");
    return false;
  }
  if (!json_node["size"].isString()) {
    qWarning("Parsing card from json node has failed. Node is not an String: \"size\"");
    return false;
  }
  QPageSize size = stringToSize(json_node["size"].toString());
  setSize(size);

  if (!json_node.contains("front")) {
    qWarning("Parsing card from json node has failed. Missing field: \"front\"");
    return false;
  }
  if (!json_node["front"].isObject()) {
    qWarning("Parsing card from json node has failed. Node is not an object: \"front\"");
    return false;
  }
  QJsonObject front_node = json_node["front"].toObject();
  parseCard(front_node, Card::Site::FRONT);

  if (!json_node.contains("back")) {
    qWarning("Parsing card from json node has failed. Missing field: \"back\"");
    return false;
  }
  if (!json_node["back"].isObject()) {
    qWarning("Parsing card from json node has failed. Node is not an object: \"back\"");
    return false;
  }
  QJsonObject back_node = json_node["back"].toObject();
  parseCard(back_node, Card::Site::BACK);

  return true;
}

bool Card::write(QJsonObject &json_node) {
  json_node.insert("orientation", orientationToString(this->card_orientation_));
  json_node.insert("size", sizeToString(this->card_size_));

  QJsonObject front_object;
  writeCard(front_object, Site::FRONT);
  json_node.insert("front", front_object);

  QJsonObject back_object;
  writeCard(back_object, Site::BACK);
  json_node.insert("back", back_object);

  return true;
}

Card::Style Card::getStyle(Card::Site site) {
  return styles_[site];
}

Field *Card::getField(const QString &name, Site site) {
  for (Field *field:card_fields_[site]) {
    if (field->name() == name) return field;
  }
  return nullptr;
}

QPageLayout::Orientation Card::orientation() {
  return this->card_orientation_;
}

QPageSize Card::size() {
  return this->card_size_;
}

void Card::setStyle(Card::Site site, Card::Style style) {
  // Check if really something changed
  if (this->styles_[site] == style) return;
  this->styles_[site] = style;
  emit styleChanged(site, style);
}

void Card::setOrientation(QPageLayout::Orientation orientation) {
  // Check if something has changed
  if (orientation == card_orientation_) return;
  this->card_orientation_ = orientation;

  emit orientationChanged(this->card_orientation_);
}

void Card::setSize(const QPageSize &size) {
  // Check if something has changed
  if (this->card_size_ == size) return;
  this->card_size_ = size;

  emit sizeChanged(this->card_size_);
}

QString Card::toString() {
  QString message;
  message += "[Card] {";
  message += "\n Orientation: " + orientationToString(this->card_orientation_);
  message += "\n Sie: " + sizeToString(this->card_size_);
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
