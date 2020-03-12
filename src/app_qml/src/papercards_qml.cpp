/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file papercards.cpp
 */
#define APPLICATION_NAME "Papercards-QML"
#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define REVISION 1

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QFontDatabase>

#include "Backend.h"

int main(int argc, char *argv[]) {
  qInfo("Executing %s, version %i.%i.%i",
        APPLICATION_NAME, MAJOR_VERSION, MINOR_VERSION, REVISION);
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication::setOrganizationName("Team Koeln");
  QGuiApplication::setApplicationName("Papercards");
  QGuiApplication::setApplicationVersion(
      QString(
          QString::number(MAJOR_VERSION) + "." +
              QString::number(MINOR_VERSION) + "." +
              QString::number(REVISION)
      ));

  QGuiApplication application(argc, argv);
  qInfo("Initiating background management.");
  Card *default_card = new Card;
  BackEnd::instance()->setCurrentCard(default_card);
  // Model::instance()->init();
  qInfo("Load config files.");
  //Model::instance()->loadConfig();

  qmlRegisterSingletonType<BackEnd>("io.papercards.backend", 1, 0, "BackEnd", &BackEnd::qmlInstance);
  qmlRegisterType<Card>("io.papercards.card", 1, 0, "Card");
  //QQuickStyle::setStyle("Fusion");

  qint32 fontId = QFontDatabase::addApplicationFont(":/assets/WorkSans-Regular.ttf");
  QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);

  QString family = fontList.at(0);
  QGuiApplication::setFont(QFont(family));

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

  auto return_code = QGuiApplication::exec();

  qInfo("Store config files.");
  //Model::instance()->storeConfig();
  qInfo("Free background management.");
  //Model::instance()->free();

  qInfo("Terminating %s", APPLICATION_NAME);
  return return_code;
}
