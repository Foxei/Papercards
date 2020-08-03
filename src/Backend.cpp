#include <QFontDatabase>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QList>
#include <QtGui/QImageReader>
#include <QtQml/QQmlFile>
#include <QtCore/QFileInfo>
#include <utility>
#include <QQmlFileSelector>
#include <QFileSelector>

#include <QPdfWriter>
#include <QPageLayout>
#include <QtGui/QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QTextBlock>

#include "Backend.h"

BackEnd *BackEnd::only_instance_ = nullptr;

BackEnd::BackEnd(QObject *parent) : QObject(parent) {}

BackEnd *BackEnd::instance() {
  if (only_instance_ == nullptr) // avoid creation of new instances
    only_instance_ = new BackEnd;
  return only_instance_;
}

QObject *BackEnd::qmlInstance(QQmlEngine */*engine*/,
                              QJSEngine */*scriptEngine*/) {
  return BackEnd::instance();
}

void BackEnd::onComplete() {
  qInfo("Parsing Font sizes from database.");
  QStringList default_font_sizes_list;
  for (auto number: QFontDatabase::standardSizes()) {
    default_font_sizes_list << QString::number(number);
  }
  this->default_font_sizes_.append(default_font_sizes_list);
  qInfo("Found %i font sizes in database.", this->default_font_sizes_.length());
  emit defaultFontSizesChanged();
}

bool BackEnd::isUrlValid() {
  bool valid = true;
  if (this->file_url_.toLocalFile().startsWith(":")) valid = false;
  if (this->file_url_.toLocalFile().isEmpty()) valid = false;
  return valid;
}

void BackEnd::addNewCard() {
  Card *card = new Card;
  this->cards_.append(card);
  emit cardAdded(card);
}

QStringList BackEnd::defaultFontSizes() {
  return this->default_font_sizes_;
}

void BackEnd::setDefaultFontSizes(const QStringList &default_font_sizes) {
  this->default_font_sizes_ = default_font_sizes;
}

Card *BackEnd::currentCard() {
  return this->current_card_;
}

void BackEnd::setCurrentCard(Card *card) {
  this->current_card_ = card;
  emit currentCardChanged();
}

const QList<Card *> &BackEnd::cards() {
  return this->cards_;
}

void BackEnd::setCards(QList<Card *> cards) {
  this->cards_ = std::move(cards);
  emit cardsChanged();
}

QString BackEnd::fileName() const {
  const QString filePath = QQmlFile::urlToLocalFileOrQrc(file_url_);
  const QString fileName = QFileInfo(filePath).fileName();
  if (fileName.isEmpty())
    return QStringLiteral("untitled.json");
  return fileName;
}

QString BackEnd::fileType() const {
  return QFileInfo(fileName()).suffix();
}

QUrl BackEnd::fileUrl() const {
  return file_url_;
}

bool BackEnd::modified() const {
  return this->modified_;
}

void BackEnd::setModified(bool m) {
  this->modified_ = m;
}

bool BackEnd::loadDefaultDeck() {
  // Try used stored file
  QString file_name = "./default_deck.json";
  if (!QFile::exists(file_name)) {
    qInfo() << "No user default deck found. Parsing system version!";
    // Try system stored file
    file_name = ":resources/default_deck.json";
  } else {
    qInfo() << "User default deck found.";
  }
  load(QUrl::fromLocalFile(file_name));
  return true;
}

void BackEnd::storeDefaultDeck() {
  QString file_name = "./default_deck.json";
  saveAs(QUrl::fromLocalFile(file_name));
}

bool BackEnd::checkIfValidImage(const QList<QUrl> &uri_list) {
  if (uri_list.length() > 1) {
    qInfo("[BackEnd] File list should only contain a single valid image. Rejected!");
    return false;
  }
  const QUrl &uri = uri_list.front();
  QString uri_string = uri.toString(QUrl::RemoveScheme).normalized(QString::NormalizationForm_D, QChar::Unicode_10_0);
  QImageReader reader(uri_string);

  bool accepted = reader.canRead();
  qInfo("[BackEnd] File test for valid image: %s!", accepted ? "Accepted" : "Rejected");
  return accepted;
}

void BackEnd::load(const QUrl &fileUrl) {
  if (fileUrl == file_url_) return;
  qInfo() << "Parsing cards from json deck:" << fileUrl;

  const QString fileName = fileUrl.toLocalFile();
  if (!QFile::exists(fileName)) {
    qWarning() << "Parsing deck from json file has failed. File not found:" << fileName;
    return;
  }

  this->cards_.clear();
  emit cleared();

  QFile file(fileName);

  // Load file into memory
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString content = file.readAll();
  file.close();

  // Parse json from file
  QJsonDocument config_document = QJsonDocument::fromJson(content.toUtf8());
  QJsonObject root_node = config_document.object();
  if (!root_node.contains("name")) {
    qWarning("Parsing deck from json node has failed. Missing field: \"name\"");
    return;
  }
  if (!root_node["name"].isString()) {
    qWarning("Parsing card from json node has failed. Node is not a String: \"name\"");
    return;
  }
  QString name = root_node["name"].toString();

  if (!root_node.contains("cards")) {
    qWarning("Parsing deck from json node has failed. Missing field: \"cards\"");
    return;
  }
  if (!root_node["cards"].isArray()) {
    qWarning("Parsing card from json node has failed. Node is not an Array: \"cards\"");
    return;
  }
  QJsonArray array = root_node["cards"].toArray();
  for (QJsonValue value : array) {
    Card *card = new Card;
    QJsonObject object = value.toObject();
    bool return_value = card->parse(object);
    if (!return_value) {
      qWarning("Parsing cards from json node has failed. Error during array passthrough.");
      return;
    }
    this->cards_.append(card);
  }
  this->current_card_ = this->cards_.first();
  qInfo() << "Parsing cards from json deck finished!";

  emit loaded();
  file_url_ = fileUrl;
  emit fileUrlChanged();
}

void BackEnd::saveAs(const QUrl &fileUrl) {
  const QString filePath = fileUrl.toLocalFile();
  QFile file(filePath);
  if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
    qWarning() << "Cannot save: " + file.errorString();
    return;
  }

  // Json root object
  QJsonObject root_node;
  root_node.insert("name", "Default Deck");

  QJsonArray card_array;
  for (Card *card : this->cards_) {
    QJsonObject object;
    card->write(object);
    card_array.append(object);
  }
  root_node["cards"] = card_array;

  // Write json from file
  QJsonDocument config_document(root_node);
  file.write(config_document.toJson());
  file.close();

  emit saved();

  if (fileUrl == file_url_)
    return;

  file_url_ = fileUrl;
  emit fileUrlChanged();
}

void BackEnd::newDeck() {
  emit cleared();
  this->cards_.clear();

  Card *card = new Card;
  this->cards_.append(card);
  this->current_card_ = this->cards_.first();
  emit loaded();

  file_url_.clear();
  emit fileUrlChanged();
}

QString injectHtmlColorSet(const QString &text){
  QString buffer = text;
  int index = buffer.indexOf("font-style:normal;");
  buffer.insert(index, "color:#000000;");
  return buffer;
}

void BackEnd::exportAsPdf(const QUrl &fileUrl) {
  const QString filePath = fileUrl.toLocalFile();
  QFile file(filePath);
  if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
    qWarning() << "Cannot save: " + file.errorString();
    return;
  }
  QPdfWriter writer(filePath);
  writer.setCreator("Simon Schäfer");
  writer.setPdfVersion(QPagedPaintDevice::PdfVersion_A1b);
  writer.setResolution(130);
  writer.setTitle("Tests Deck");

  QPageSize page_size = QPageSize(QPageSize::A6);
  QPageLayout::Orientation page_orientation = QPageLayout::Orientation::Landscape;
  QMarginsF page_margins = QMarginsF(20,20,20,20);
  QPageLayout page_layout = QPageLayout(page_size, page_orientation, page_margins);
  writer.setPageLayout(page_layout);

  QPainter painter;

  painter.begin(&writer);
  for (Card *card : this->cards_) {
    writer.newPage();
    QTextDocument print_document;

    print_document.setPageSize(painter.viewport().size());
    painter.setClipRect(painter.viewport());

    print_document.setHtml(injectHtmlColorSet(card->cardQuestionText()));
    print_document.drawContents(&painter);

    writer.newPage();
    print_document.setHtml(injectHtmlColorSet(card->cardAnswerText()));
    print_document.drawContents(&painter);
  }
  painter.end();

  emit exported();
}


