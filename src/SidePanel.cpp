#include "SidePanel.h"
#include "ui_sidepanel.h"

#include <QDebug>

SidePanel::SidePanel(QWidget *parent) : QWidget(parent), ui(new Ui::sidePanel) {
  ui->setupUi(this);
}

SidePanel::~SidePanel() {
  delete ui;
}
