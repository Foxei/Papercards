#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "Backend.h"

int main(int argc, char *argv[]) {
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  qmlRegisterType<BackEnd>("io.papercards.backend", 1, 0, "BackEnd");

  QQuickStyle::setStyle("Material");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

  return QGuiApplication::exec();
}