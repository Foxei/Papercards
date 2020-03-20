#ifndef PAPER_CARDS_QML_BACKEND_H
#define PAPER_CARDS_QML_BACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QStringList>

#include "model/Card.h"

class BackEnd : public QObject {
  // @formatter::off
  Q_OBJECT
  Q_PROPERTY(QStringList available_font_families READ availableFontFamilies WRITE setAvailableFontFamilies NOTIFY availableFontFamiliesChanged)
  Q_PROPERTY(QStringList default_font_sizes READ defaultFontSizes WRITE setDefaultFontSizes NOTIFY defaultFontSizesChanged)
  Q_PROPERTY(Card* current_card READ currentCard WRITE setCurrentCard NOTIFY currentCardChanged)
  // @formatter::on

 private:
  QStringList available_font_families_;
  QStringList default_font_sizes_;
  Card *current_card_ = nullptr;

  static BackEnd* only_instance_;
  explicit BackEnd(QObject *parent = nullptr);

 public:
  static BackEnd *instance();
  static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

  Q_INVOKABLE void onComplete();

  QStringList availableFontFamilies();
  QStringList defaultFontSizes();
  Card* currentCard();


 public slots:
  void setAvailableFontFamilies(const QStringList &available_font_families);
  void setDefaultFontSizes(const QStringList &default_font_sizes);
  void setCurrentCard(Card* card);

  bool loadCurrentCard(const QString &file_name);
  bool storeCurrentCard(const QString &file_name);
  static bool checkIfValidImage(const QList<QUrl> &uri_list);

 signals:

  #pragma clang diagnostic push
  #pragma ide diagnostic ignored "NotImplementedFunctions"
  void availableFontFamiliesChanged();
  void defaultFontSizesChanged();
  void currentCardChanged();
  #pragma clang diagnostic pop

};

#endif //PAPER_CARDS_QML_BACKEND_H
