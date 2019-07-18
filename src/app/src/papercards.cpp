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
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QStyleFactory>

#include <memory>

#include "view/MainWindow.h"
#include "view/ColorDefinitions.h"

/**
 * @brief Initiates background management.
 *
 */
void initiateDataManager(){}

/**
 * @brief Load config files.
 *
 */
void loadConfigFiles(){}

/**
 * @brief Store config files.
 *
 */
void storeConfigFiles(){

}

/**
 * @brief Frees background management.
 */
void freeDataManager(){}

/**
 * @brief Setting style to dark theme and cross platform fonts
 * @param application Application were the style will be changed
 */
void setStyle(QApplication* application)
{
  qInfo("Do app style processing");
  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, Color::BACKGROUND);
  darkPalette.setColor(QPalette::WindowText, Color::WHITE);
  darkPalette.setColor(QPalette::Base, Color::BASE);
  darkPalette.setColor(QPalette::AlternateBase, Color::BACKGROUND);
  darkPalette.setColor(QPalette::ToolTipBase, Color::BASE);
  darkPalette.setColor(QPalette::ToolTipText, Color::WHITE);
  darkPalette.setColor(QPalette::Text, Color::WHITE);
  darkPalette.setColor(QPalette::Button, Color::BACKGROUND);
  darkPalette.setColor(QPalette::ButtonText, Color::WHITE);
  darkPalette.setColor(QPalette::BrightText, Color::BASE);
  darkPalette.setColor(QPalette::Link, Color::CYAN);

  darkPalette.setColor(QPalette::Highlight, Color::BLUE);
  darkPalette.setColor(QPalette::HighlightedText, Color::WHITE);

  // Stylesheet
  qInfo("Loading Stylesheet: %s", "res/stylesheet.qss");
  QFile file_stylesheet("res/stylesheet.qss");
  file_stylesheet.open(QFile::ReadOnly);
  QString stylesheet = QLatin1String(file_stylesheet.readAll());

  // Setup Fusion style
  qInfo("Loading Style: %s" , "Fusion");
  QApplication::setPalette(darkPalette);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  application->setStyleSheet(stylesheet);

  qInfo("Setting font: %s", "res/WorkSans-Light.ttf");
  QFileInfo file_font("res/WorkSans-Light.ttf");
  QFontDatabase::addApplicationFont(file_font.absoluteFilePath());

  QFileInfo file_icon("res/document_orientation_landscape.png");
  QApplication::setWindowIcon(QIcon(file_icon.absoluteFilePath()));

  qInfo("Finished app style processing");
  qInfo("");
}

int main(int argc, char* argv[]) {
  qInfo("Executing %s, version %i.%i.%i",
      APPLICATION_NAME, MAJOR_VERSION, MINOR_VERSION, REVISION);
  std::unique_ptr<QApplication> application =
      std::make_unique<QApplication>(argc, argv);

  application->setOrganizationName("Team Koeln");
  application->setApplicationName("Papercards");
  application->setApplicationVersion(
      QString(
          QString::number(MAJOR_VERSION)+"."+
          QString::number(MINOR_VERSION)+"."+
          QString::number(REVISION)
          ));

  setStyle(application.get());

  qInfo("Initiating background management");
  initiateDataManager();
  qInfo("Load config file");
  loadConfigFiles();

  std::unique_ptr<MainWindow> main_window =
      std::make_unique<MainWindow>();
  main_window->show();

  int return_value = application->exec();

  qInfo("Store config file");
  storeConfigFiles();
  qInfo("Free background management");
  freeDataManager();

  qInfo("Terminating %s", APPLICATION_NAME);
  return return_value;
}