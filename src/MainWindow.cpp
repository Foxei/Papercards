#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow) {
  ui->setupUi(this);
  setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow() {
  delete ui;
}
