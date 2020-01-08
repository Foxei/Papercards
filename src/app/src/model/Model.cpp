#include "Model.h"

#include <memory>

#include <QString>
#include <QJsonDocument>
#include <QFile>

bool Model::loadDefaultCard(const QString &file_name) {
  // Check if default card was allocated
  if(!default_card) return false;
  // Check if file exists
  QFile file(file_name);
  if (!file.exists()) return false;

  // Load file into memory
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString content = file.readAll();
  file.close();

  // Parse json from file
  QJsonDocument config_document = QJsonDocument::fromJson(content.toUtf8());
  QJsonObject root_node = config_document.object();

  // Parse card from json
  bool card_parsing_succeeded = default_card->parseConfig(root_node);
  return card_parsing_succeeded;
}

void Model::init() {
  default_card = std::make_shared<Card>();
}

bool Model::loadConfig() {
  bool return_value = true;

  qInfo("Loading default card from file.");
  QString file_name = ":default_card.json";
  bool card_parsing_succeeded = loadDefaultCard(file_name);
  if(card_parsing_succeeded)
    qDebug("Default card loaded: \n%s",default_card->toString().toStdString().c_str());
  else{
    qWarning("Parsing default card failed.");
    return_value = false;
  }

  return return_value;
}

bool Model::storeConfig() {

}

void Model::free() {
}

std::weak_ptr<Card> Model::defaultCard() {
  return std::weak_ptr<Card>(this->default_card);
}
