#include <QtGui/QFontDatabase>
#include "Backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent) {}

void BackEnd::onComplete() {
  qInfo("Interface ready!");

  qInfo("Parsing Font families from database.");
  QFontDatabase font_database;
  QStringList default_font_families_list;
  for (const auto &family: font_database.families()) {
    if (family.startsWith(".")) continue;
    default_font_families_list << family;
  }
  this->_available_font_families.append(default_font_families_list);
  qInfo("Found %i font families in database.", this->_available_font_families.length());
  emit availableFontFamiliesChanged();

  qInfo("Parsing Font sizes from database.");
  QStringList default_font_sizes_list;
  for (auto number: QFontDatabase::standardSizes()) {
    default_font_sizes_list << QString::number(number);
  }
  this->_default_font_sizes.append(default_font_sizes_list);
  qInfo("Found %i font sizes in database.", this->_default_font_sizes.length());
  emit defaultFontSizesChanged();
}

QStringList BackEnd::availableFontFamilies() {
  return this->_available_font_families;
}

QStringList BackEnd::defaultFontSizes() {
  return this->_default_font_sizes;
}

void BackEnd::setAvailableFontFamilies(const QStringList &available_font_families) {
  this->_available_font_families = available_font_families;
}

void BackEnd::setDefaultFontSizes(const QStringList &default_font_sizes) {
  this->_default_font_sizes = default_font_sizes;
}
