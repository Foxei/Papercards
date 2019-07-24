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
  setBackgroundRole(QPalette::WindowText);

  auto* action_clipboard = addAction(QIcon(":clipboard.png"), QString("clipboard"));

  addSeparator();

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

  addSeparator();

  auto* action_bold = addAction(QIcon(":font_bold.png"), QString("bold"));
  action_bold->setCheckable(true);
  auto* action_italic = addAction(QIcon(":font_italic.png"), QString("italic"));
  action_italic->setCheckable(true);
  auto* action_underlined = addAction(QIcon(":font_underlined.png"), QString("underlined"));
  action_underlined->setCheckable(true);

  addSeparator();

  auto* action_color = addAction(QIcon(":font_color.png"), QString("color"));
  auto* action_highlight = addAction(QIcon(":highlighter.png"), QString("highlight"));

  addSeparator();

  auto* action_bullet = addAction(QIcon(":bullet.png"), QString("bullet"));
  action_bullet->setCheckable(true);
  auto* action_decrease = addAction(QIcon(":decrease_indentation.png"), QString("decrease"));
  auto* action_increase = addAction(QIcon(":increase_indentation.png"), QString("increase"));
}

void CardEditorToolbar::setupConnections() {

}

CardEditorToolbar::CardEditorToolbar(QWidget *parent) : QToolBar(parent) {
  setObjectName(QString("card_editor_toolbar"));

  setupGui();
  setupConnections();
}