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
#include <QIcon>

#include "Backend.h"
#include "DocumentHandler.h"

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
  QGuiApplication::setWindowIcon(QIcon(":/resources/logo.png"));

  qInfo("Initiating background management.");
  Card *default_card = new Card;
  BackEnd::instance()->setCurrentCard(default_card);

  qInfo("Loading default card from file.");
  QString file_name = ":resources/default_card.json";
  bool card_parsing_succeeded = BackEnd::instance()->loadCurrentCard(file_name);
  if (card_parsing_succeeded)
    qDebug("Default card loaded.");
  else {
    qWarning("Parsing default card failed.");
  }

  qmlRegisterSingletonType<BackEnd>("io.papercards.backend",
                                    1,
                                    0,
                                    "BackEnd",
                                    &BackEnd::qmlInstance);
  qmlRegisterType<Card>("io.papercards.card", 1, 0, "Card");
  qmlRegisterType<DocumentHandler>("io.papercards.texteditor", 1, 0, "DocumentHandler");


  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

  auto return_code = QGuiApplication::exec();

  qInfo("Store config files.");
  qInfo("Free background management.");

  qInfo("Terminating %s", APPLICATION_NAME);
  return return_code;
}
