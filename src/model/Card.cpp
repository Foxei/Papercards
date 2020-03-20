#include "Card.h"

#include <QJsonObject>
#include <QPageSize>
#include <utility>

Card::CardOrientation stringToOrientation(const QString &style_string) {
  if (style_string == "portrait") {
    return Card::CardOrientation::Portrait;
  }
  return Card::CardOrientation::Landscape;
}

QString orientationToString(const Card::CardOrientation &orientation) {
  switch (orientation) {
    case Card::CardOrientation::Landscape: return "landscape";
    case Card::CardOrientation::Portrait: return "portrait";
  }
}

QRectF stringToSize(const QString &style_string) {
  if (style_string == "A5") {
    return QPageSize(QPageSize::A5).rect(QPageSize::Unit::Millimeter);
  }
  // Fallback size
  return QPageSize(QPageSize::A6).rect(QPageSize::Unit::Millimeter);
}

QString sizeToString(const QRectF &size) {
  if (QPageSize(QPageSize::A5).rect(QPageSize::Unit::Millimeter) == size) {
    return "A5";
  }
  // Fallback size
  return "A6";
}

Card::Card(QObject *parent) : QObject(parent) {
  // Default card
  card_size_ = stringToSize("A6");
  card_orientation_ = Card::CardOrientation::Landscape;

  if (card_orientation_ == Card::CardOrientation::Landscape) {
    auto buffer = this->card_size_;
    this->card_size_.setWidth(buffer.height());
    this->card_size_.setHeight(buffer.width());
  }
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
  CardOrientation orientation = stringToOrientation(json_node["orientation"].toString());
  setCardOrientation(orientation);

  if (!json_node.contains("size")) {
    qWarning("Parsing card from json node has failed. Missing field: \"size\"");
    return false;
  }
  if (!json_node["size"].isString()) {
    qWarning("Parsing card from json node has failed. Node is not an String: \"size\"");
    return false;
  }
  QRectF size = stringToSize(json_node["size"].toString());
  if (card_orientation_ == Card::CardOrientation::Landscape) {
    auto buffer = size;
    size.setWidth(buffer.height());
    size.setHeight(buffer.width());
  }
  setCardSize(size);

  if (!json_node.contains("question")) {
    qWarning("Parsing card from json node has failed. Missing field: \"question\"");
    return false;
  }
  if (!json_node["question"].isString()) {
    qWarning("Parsing card from json node has failed. Node is not an String: \"question\"");
    return false;
  }
  QString question = json_node["question"].toString();
  setCardQuestionText(question);

  if (!json_node.contains("answer")) {
    qWarning("Parsing card from json node has failed. Missing field: \"answer\"");
    return false;
  }
  if (!json_node["answer"].isString()) {
    qWarning("Parsing card from json node has failed. Node is not an String: \"answer\"");
    return false;
  }
  QString answer = json_node["answer"].toString();
  setCardAnswerText(answer);
  return true;
}

bool Card::write(QJsonObject &json_node) {
  json_node.insert("orientation", orientationToString(this->card_orientation_));
  json_node.insert("size", sizeToString(this->card_size_));
  json_node.insert("question", this->card_question_text_);
  json_node.insert("answer", this->card_answer_text_);
  return false;
}

const QRectF &Card::cardSize() {
  return this->card_size_;
}

const Card::CardOrientation &Card::cardOrientation() {
  return this->card_orientation_;
}

const QString &Card::cardQuestionText() {
  return this->card_question_text_;
}

const QString &Card::cardAnswerText() {
  return this->card_answer_text_;
}

const QString &Card::text(Card::CardField field) {
  switch (field){
    case Question: return cardQuestionText();
    case Answer: return cardAnswerText();
  }
}

void Card::setCardSize(QRectF card_size) {
  this->card_size_ = card_size;
}

void Card::setCardOrientation(Card::CardOrientation card_orientation) {
  this->card_orientation_ = card_orientation;
}

void Card::setCardQuestionText(QString card_question_text) {
  this->card_question_text_ = std::move(card_question_text);
}

void Card::setCardAnswerText(QString card_answer_text) {
  this->card_answer_text_ = std::move(card_answer_text);
}

void Card::updateText(const QString& text, Card::CardField field) {
  switch (field) {
    case Question:
      setCardQuestionText(text);
      break;
    case Answer:
      setCardAnswerText(text);
      break;
  }
}


