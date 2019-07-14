/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file papercards.cpp
 */
#define APPLICATION_NAME "Papercards"
#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define REVISION 1

#include <QtCore/QMessageLogger>
#include <QtCore/QSettings>

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

int main() {
  qInfo("Executing %s, version %i.%i.%i",
      APPLICATION_NAME, MAJOR_VERSION, MINOR_VERSION, REVISION);

  qInfo("Initiating background management");
  initiateDataManager();
  qInfo("Load config file");
  loadConfigFiles();

  qInfo("Store config file");
  storeConfigFiles();
  qInfo("Free background management");
  freeDataManager();

  qInfo("Terminating %s", APPLICATION_NAME);
  return 0;
}