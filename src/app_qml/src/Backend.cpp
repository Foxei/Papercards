#include <QtGui/QFontDatabase>
#include "Backend.h"

BackEnd *BackEnd::only_instance_ = nullptr;

BackEnd::BackEnd(QObject *parent) : QObject(parent) {}

BackEnd *BackEnd::instance() {
  if (only_instance_ == nullptr) // avoid creation of new instances
    only_instance_ = new BackEnd;
  return only_instance_;
}

QObject *BackEnd::qmlInstance(QQmlEngine */*engine*/, QJSEngine */*scriptEngine*/) {
  return BackEnd::instance();
}

void BackEnd::onComplete() {
  qInfo("Interface ready!");

  qInfo("Parsing Font families from database.");
  QFontDatabase font_database;
  QStringList default_font_families_list;
  for (const auto &family: font_database.families()) {
    if (family.startsWith(".")) continue;
    default_font_families_list << family;
  }
  this->available_font_families_.append(default_font_families_list);
  qInfo("Found %i font families in database.", this->available_font_families_.length());
  emit availableFontFamiliesChanged();

  qInfo("Parsing Font sizes from database.");
  QStringList default_font_sizes_list;
  for (auto number: QFontDatabase::standardSizes()) {
    default_font_sizes_list << QString::number(number);
  }
  this->default_font_sizes_.append(default_font_sizes_list);
  qInfo("Found %i font sizes in database.", this->default_font_sizes_.length());
  emit defaultFontSizesChanged();
}

QStringList BackEnd::availableFontFamilies() {
  return this->available_font_families_;
}

QStringList BackEnd::defaultFontSizes() {
  return this->default_font_sizes_;
}

Card *BackEnd::currentCard() {
  return this->current_card_;
}

void BackEnd::setAvailableFontFamilies(const QStringList &available_font_families) {
  this->available_font_families_ = available_font_families;
}

void BackEnd::setDefaultFontSizes(const QStringList &default_font_sizes) {
  this->default_font_sizes_ = default_font_sizes;
}

void BackEnd::setCurrentCard(Card *card) {
  this->current_card_ = card;
  emit currentCardChanged();
}

