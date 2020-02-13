#ifndef PAPER_CARDS_QML_BACKEND_H
#define PAPER_CARDS_QML_BACKEND_H

#include <QObject>
#include <QStringList>

class BackEnd : public QObject {
  // @formatter::off
  Q_OBJECT
  Q_PROPERTY(QStringList available_font_families READ availableFontFamilies WRITE setAvailableFontFamilies NOTIFY availableFontFamiliesChanged)
  Q_PROPERTY(QStringList default_font_sizes READ defaultFontSizes WRITE setDefaultFontSizes NOTIFY defaultFontSizesChanged)
  // @formatter::on

 private:
  QStringList _available_font_families;
  QStringList _default_font_sizes;

 public:
  explicit BackEnd(QObject *parent = nullptr);

  Q_INVOKABLE void onComplete();

  QStringList availableFontFamilies();
  QStringList defaultFontSizes();

  void setAvailableFontFamilies(const QStringList &available_font_families);
  void setDefaultFontSizes(const QStringList &default_font_sizes);

 signals:
  void availableFontFamiliesChanged();
  void defaultFontSizesChanged();

};

#endif //PAPER_CARDS_QML_BACKEND_H
