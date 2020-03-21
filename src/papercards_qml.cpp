/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file papercards.cpp
 */
#define APPLICATION_NAME "Papercards"
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

void init_application_information(){
 //  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication::setOrganizationName("Team Koeln");
  QGuiApplication::setApplicationName("Papercards");
  QGuiApplication::setApplicationVersion(
    QString(
      QString::number(MAJOR_VERSION) + "." +
        QString::number(MINOR_VERSION) + "." +
        QString::number(REVISION)
    ));
}

void register_qml() {
  qmlRegisterSingletonType<BackEnd>("io.papercards.backend", 1, 0, "BackEnd", &BackEnd::qmlInstance);
  qmlRegisterType<Card>("io.papercards.card", 1, 0, "Card");
  qmlRegisterType<DocumentHandler>("io.papercards.texteditor", 1, 0, "DocumentHandler");
}

int main(int argc, char *argv[]) {
  qInfo("Executing %s, version %i.%i.%i.", APPLICATION_NAME, MAJOR_VERSION, MINOR_VERSION, REVISION);
  init_application_information();

  QGuiApplication application(argc, argv);
  QGuiApplication::setWindowIcon(QIcon(":/resources/logo.png"));

  qInfo("Loading default card from file.");
  BackEnd::instance()->newDeck();

  qInfo("Executing qml and java script.");
  register_qml();
  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

  auto return_code = QGuiApplication::exec();

  qInfo("Terminating %s.", APPLICATION_NAME);
  return return_code;
}
