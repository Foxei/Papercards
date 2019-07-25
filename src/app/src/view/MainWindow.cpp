/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file MainWindow.cpp
 */

#include "MainWindow.h"

#include <QSettings>
#include <QDateTime>

void MainWindow::setupGui() {
  restoreWindowStates();
  setMinimumSize(QSize(800, 600));

  card_editor = new CardEditor(this);
  card_editor_toolbar = new CardEditorToolBar(this);
  status_bar = new StatusBar(this);

  setCentralWidget(card_editor);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, card_editor_toolbar);
  setStatusBar(status_bar);

  QDateTime current_time = QDateTime::currentDateTime();
  QString
      current_time_string = current_time.toString(Qt::DateFormat::LocalDate);

  status_bar->showMessage(QString(
      "Application started on: " + current_time_string));
}

void MainWindow::setupConnections() {
  // Pass through the scale by scroll wheel events
  connect(card_editor,
          &CardEditor::scaleFactorChanged,
          status_bar,
          &StatusBar::setScaleFactor);
  // Pass through the scale by slider events
  connect(status_bar,
          &StatusBar::scaleFactorChanged,
          card_editor,
          &CardEditor::setScaleFactor);
}

void MainWindow::restoreWindowStates() {
  QSettings settings
      (QSettings::IniFormat, QSettings::UserScope, "Papercards", "Window");
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("window_state").toByteArray());
}

void MainWindow::storeWindowState() {
  QSettings settings
      (QSettings::IniFormat, QSettings::UserScope, "Papercards", "Window");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("window_state", saveState());
}

void MainWindow::closeEvent(QCloseEvent *event) {
  storeWindowState();
  QMainWindow::closeEvent(event);
}

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(
    parent,
    flags) {
  this->setupGui();
  this->setupConnections();

  QSettings settings
      (QSettings::IniFormat, QSettings::UserScope, "Papercards", "Editor");
  qreal scale_factor = settings.value("scale_factor", qreal(1.0)).toReal();
  card_editor->setScaleFactor(scale_factor);
}
