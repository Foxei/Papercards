/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file papercards.cpp
 */
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QFontDatabase>
#include <QIcon>
#include <QDebug>

#include "MainWindow.h"


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
  const auto id = QFontDatabase::addApplicationFont(":/resources/feather.ttf");
  qDebug() << QFontDatabase::applicationFontFamilies(id).front();
}

/*
void register_qml() {
  qmlRegisterSingletonType<BackEnd>("io.papercards.backend", 1, 0, "BackEnd", &BackEnd::qmlInstance);
  qmlRegisterType<Card>("io.papercards.card", 1, 0, "Card");
  qmlRegisterType<DocumentHandler>("io.papercards.texteditor", 1, 0, "DocumentHandler");
}
*/

int main(int argc, char *argv[]) {
  qInfo("Executing Papercards, Version %i.%i.%i.", MAJOR_VERSION, MINOR_VERSION, REVISION);
  init_application_information();

  QApplication application(argc, argv);
  QApplication::setWindowIcon(QIcon(":/resources/logo.png"));

  qInfo("Loading default card from file.");
  //BackEnd::instance()->newDeck();

  qInfo("Loading fonts.");
  load_fonts();

  QIcon::setThemeName( "papercards-icon-theme" );
  
  qInfo("Executing qml and java script.");
  //register_qml();
  //QQmlApplicationEngine engine;
  //engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

  auto* window = new MainWindow;
  window->show();
  auto return_code = QApplication::exec();

  qInfo("Terminating .");
  return return_code;
}
