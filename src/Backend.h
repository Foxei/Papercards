#ifndef PAPER_CARDS_QML_BACKEND_H
#define PAPER_CARDS_QML_BACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QStringList>

#include "model/Card.h"

class BackEnd : public QObject {
  // @formatter::off
  Q_OBJECT
  Q_PROPERTY(QStringList default_font_sizes READ defaultFontSizes WRITE setDefaultFontSizes NOTIFY defaultFontSizesChanged)
  Q_PROPERTY(Card* current_card READ currentCard WRITE setCurrentCard NOTIFY currentCardChanged)
  Q_PROPERTY(QList<Card*> cards READ cards WRITE setCards NOTIFY cardsChanged)
  Q_PROPERTY(QString fileName READ fileName NOTIFY fileUrlChanged)
  Q_PROPERTY(QString fileType READ fileType NOTIFY fileUrlChanged)
  Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
  Q_PROPERTY(bool modified READ modified WRITE setModified NOTIFY modifiedChanged)
  // @formatter::on

 private:
  QStringList default_font_sizes_;
  Card *current_card_ = nullptr;
  QList<Card*> cards_;
  QUrl file_url_;
  bool modified_ = false;

  static BackEnd* only_instance_;
  explicit BackEnd(QObject *parent = nullptr);

 public:
  static BackEnd *instance();
  static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

  Q_INVOKABLE void onComplete();
  Q_INVOKABLE bool isUrlValid();

  QStringList defaultFontSizes();
  void setDefaultFontSizes(const QStringList &default_font_sizes);

  Card* currentCard();
  void setCurrentCard(Card* card);

  const QList<Card*>& cards();
  void setCards(QList<Card*> cards);

  QString fileName() const;
  QString fileType() const;
  QUrl fileUrl() const;

  bool modified() const;
  void setModified(bool m);

  bool loadDefaultDeck();
  void storeDefaultDeck();

 public Q_SLOTS:
  static bool checkIfValidImage(const QList<QUrl> &uri_list);
  void addNewCard();

  void load(const QUrl &fileUrl);
  void saveAs(const QUrl &fileUrl);
  void newDeck();

 Q_SIGNALS:
  #pragma clang diagnostic push
  #pragma ide diagnostic ignored "NotImplementedFunctions"
  void defaultFontSizesChanged();
  void currentCardChanged();
  void cardsChanged();
  void cardAdded(Card*);
  void fileUrlChanged();
  void modifiedChanged();
  void loaded();
  void saved();
  void cleared();
#pragma clang diagnostic pop

};

#endif //PAPER_CARDS_QML_BACKEND_H
