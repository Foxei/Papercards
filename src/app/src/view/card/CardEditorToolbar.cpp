/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file CardEditorToolbar.h
 */

#include "CardEditorToolbar.h"

#include <QComboBox>
#include <QFontDatabase>
#include <QListView>
#include <QStyledItemDelegate>
#include <QStringList>

void CardEditorToolbar::setupGui() {
  setMovable(false);
  setFloatable(false);

  auto* dummy = new QComboBox(this);
  QFontDatabase font_database;
  dummy->addItems(font_database.families());
  dummy->setMaxVisibleItems(5);
  dummy->setEditable(true);
  dummy->setItemDelegate(new QStyledItemDelegate());

  addWidget(dummy);

  auto* dummy1 = new QComboBox(this);
  dummy1->setMaxVisibleItems(5);
  dummy1->setEditable(true);
  dummy1->setItemDelegate(new QStyledItemDelegate());

  QStringList dummy1_list;
  for(int number: QFontDatabase::standardSizes()) {
    dummy1_list << QString::number(number);
  }
  dummy1->addItems(dummy1_list);

  QValidator* validator1 = new QIntValidator;
  auto* int_validator1 = qobject_cast<QIntValidator*>(validator1);
  int_validator1->setBottom(1);
  dummy1->setValidator(validator1);

  addWidget(dummy1);
}

void CardEditorToolbar::setupConnections() {

}

CardEditorToolbar::CardEditorToolbar(QWidget *parent) : QToolBar(parent) {
  setupGui();
  setupConnections();
}