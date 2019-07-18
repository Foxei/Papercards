/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file MainWindow.cpp
 */

#include "MainWindow.h"

#include <QSettings>

void MainWindow::setupGui() {
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Papercards", "Window");
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("window_state").toByteArray());

  setMinimumSize(QSize(800,600));

  container_card = new CardEditor(this);

  setCentralWidget(container_card);
}

void MainWindow::setupConnections() {

}

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
  this->setupGui();
  this->setupConnections();
}

MainWindow::~MainWindow() {
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Papercards", "Window");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("window_state", saveState());
}