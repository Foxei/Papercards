/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file papercards.cpp
 */
#define APPLICATION_NAME "Papercards"
#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define REVISION 1

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QFontDatabase>
#include <QIcon>

#include "Backend.h"
#include "DocumentHandler.h"

void init_application_information(){
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication::setOrganizationName("Team Koeln");
  QApplication::setApplicationName("Papercards");
  QApplication::setApplicationVersion(
    QString(
      QString::number(MAJOR_VERSION) + "." +
        QString::number(MINOR_VERSION) + "." +
        QString::number(REVISION)
    ));
}

void load_fonts(){
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-BlackItalic.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-Black.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-Bold.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-BoldItalic.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-Medium.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-MediumItalic.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-Regular.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-Italic.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-Light.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-LightItalic.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-Thin.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-ThinItalic.ttf");
  QFontDatabase::addApplicationFont(":/resources/MaterialIcons-Regular.ttf");
  QFontDatabase::addApplicationFont(":/resources/roboto/Roboto-BlackItalic.ttf");
}

void register_qml() {
  qmlRegisterSingletonType<BackEnd>("io.papercards.backend", 1, 0, "BackEnd", &BackEnd::qmlInstance);
  qmlRegisterType<Card>("io.papercards.card", 1, 0, "Card");
  qmlRegisterType<DocumentHandler>("io.papercards.texteditor", 1, 0, "DocumentHandler");
}

int main(int argc, char *argv[]) {
  qInfo("Executing %s, version %i.%i.%i.", APPLICATION_NAME, MAJOR_VERSION, MINOR_VERSION, REVISION);
  init_application_information();

  QApplication application(argc, argv);
  QApplication::setWindowIcon(QIcon(":/resources/logo.png"));

  qInfo("Loading default card from file.");
  BackEnd::instance()->newDeck();

  qInfo("Loading fonts.");
  load_fonts();
  
  qInfo("Executing qml and java script.");
  register_qml();
  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

  auto return_code = QApplication::exec();

  qInfo("Terminating %s.", APPLICATION_NAME);
  return return_code;
}
