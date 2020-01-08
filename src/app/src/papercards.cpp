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
#include <QMessageLogger>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QJsonDocument>

#include <memory>

#include "view/MainWindow.h"
#include "view/ColorDefinitions.h"
#include "model/Model.h"
#include "controller/Controller.h"
#include "view/View.h"

Q_DECLARE_METATYPE(Card*)
Q_DECLARE_METATYPE(Field*)

/**
 * @brief Initiates background management.
 *
 */
void initiateDataManager(QApplication *application) {
  Model::instance()->init();
  View::instance()->init();
  Controller::instance()->init();
}

/**
 * @brief Load config files.
 *
 */
void loadConfigFiles() {
  Model::instance()->loadConfig();
}

/**
 * @brief Store config files.
 *
 */
void storeConfigFiles() {
  Model::instance()->storeConfig();
}

/**
 * @brief Frees background management.
 */
void freeDataManager() {
  Controller::instance()->free();
  View::instance()->free();
  Model::instance()->free();
}

/**
 * @brief Setting style to dark theme and cross platform fonts
 * @param application Application were the style will be changed
 */
void setStyle(QApplication *application) {
  qInfo("Do app style processing");
  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, Color::BACKGROUND);
  darkPalette.setColor(QPalette::WindowText, Color::BLACK);
  darkPalette.setColor(QPalette::Base, Color::BASE);
  darkPalette.setColor(QPalette::AlternateBase, Color::BACKGROUND);
  darkPalette.setColor(QPalette::ToolTipBase, Color::BASE);
  darkPalette.setColor(QPalette::ToolTipText, Color::BLACK);
  darkPalette.setColor(QPalette::Text, Color::BLACK);
  darkPalette.setColor(QPalette::Button, Color::BACKGROUND);
  darkPalette.setColor(QPalette::ButtonText, Color::BLACK);
  darkPalette.setColor(QPalette::BrightText, Color::WHITE);
  darkPalette.setColor(QPalette::Link, Color::CYAN);

  darkPalette.setColor(QPalette::Highlight, Color::BLUE);
  darkPalette.setColor(QPalette::HighlightedText, Color::BLACK);

  // Stylesheet
  qInfo("Loading Stylesheet: %s", "stylesheet.qss");
  QFile file_stylesheet(":stylesheet.qss");
  file_stylesheet.open(QFile::ReadOnly);
  QString stylesheet = QLatin1String(file_stylesheet.readAll());

  // Setup Fusion style
  qInfo("Loading Style: %s", "Fusion");
  QApplication::setPalette(darkPalette);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  application->setStyleSheet(stylesheet);

  qInfo("Setting font: %s", "WorkSans-Light.ttf");
  QFileInfo file_font(":WorkSans-Light.ttf");
  QFontDatabase::addApplicationFont(file_font.absoluteFilePath());

  QFileInfo file_icon(":document_orientation_landscape.png");
  QApplication::setWindowIcon(QIcon(file_icon.absoluteFilePath()));

  qInfo("Finished app style processing");
  qInfo("");
}
#include <QTimer>

int main(int argc, char *argv[]) {
  qInfo("Executing %s, version %i.%i.%i",
        APPLICATION_NAME, MAJOR_VERSION, MINOR_VERSION, REVISION);
  std::unique_ptr<QApplication> application = std::make_unique<QApplication>(argc, argv);

  application->setOrganizationName("Team Koeln");
  application->setApplicationName("Papercards");
  application->setApplicationVersion(
      QString(
          QString::number(MAJOR_VERSION) + "." +
              QString::number(MINOR_VERSION) + "." +
              QString::number(REVISION)
      ));

  setStyle(application.get());

  qInfo("Initiating background management");
  initiateDataManager(application.get());
  qInfo("Load config file");
  loadConfigFiles();

  std::shared_ptr<MainWindow> main_window = std::make_shared<MainWindow>(application.get());

  View::instance()->showMainWindow(main_window);

  int return_value = application->exec();

  qInfo("Store config file");
  storeConfigFiles();
  qInfo("Free background management");
  freeDataManager();

  qInfo("Terminating %s", APPLICATION_NAME);
  return return_value;
}