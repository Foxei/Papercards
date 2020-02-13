/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file CardEditorToolbar.h
 */

#include "CardEditorToolBar.h"

#include <QComboBox>
#include <QFontDatabase>
#include <QListView>
#include <QStyledItemDelegate>
#include <QStringList>

void CardEditorToolBar::setupGui() {
  setMovable(false);
  setFloatable(false);

  auto* action_clipboard = addAction(QIcon(":assets/clipboard.png"), QString("clipboard"));

  addSeparator();

  font_family_combobox_ = new QComboBox(this);
  QFontDatabase font_database;
  font_family_combobox_->addItems(font_database.families());
  font_family_combobox_->setMaxVisibleItems(5);
  font_family_combobox_->setEditable(false);
  font_family_combobox_->setItemDelegate(new QStyledItemDelegate());

  addWidget(font_family_combobox_);

  font_size_combobox_ = new QComboBox(this);
  font_size_combobox_->setMaxVisibleItems(5);
  font_size_combobox_->setEditable(true);
  font_size_combobox_->setItemDelegate(new QStyledItemDelegate());

  QStringList default_font_sizes_list;
  for(int number: QFontDatabase::standardSizes()) {
    default_font_sizes_list << QString::number(number);
  }
  font_size_combobox_->addItems(default_font_sizes_list);

  QValidator* validator1 = new QIntValidator;
  auto* int_validator1 = qobject_cast<QIntValidator*>(validator1);
  int_validator1->setBottom(1);
  font_size_combobox_->setValidator(validator1);

  addWidget(font_size_combobox_);

  addSeparator();

  action_bold_ = addAction(QIcon(":assets/font_bold.png"), QString("bold"));
  action_bold_->setCheckable(true);
  action_italic_ = addAction(QIcon(":assets/font_italic.png"), QString("italic"));
  action_italic_->setCheckable(true);
  action_underlined_ = addAction(QIcon(":assets/font_underlined.png"), QString("underlined"));
  action_underlined_->setCheckable(true);

  addSeparator();

  auto* action_color = addAction(QIcon(":assets/font_color.png"), QString("color"));
  auto* action_highlight = addAction(QIcon(":assets/highlighter.png"), QString("highlight"));

  addSeparator();

  auto* action_bullet = addAction(QIcon(":assets/bullet.png"), QString("bullet"));
  action_bullet->setCheckable(true);
  auto* action_decrease = addAction(QIcon(":assets/decrease_indentation.png"), QString("decrease"));
  auto* action_increase = addAction(QIcon(":assets/increase_indentation.png"), QString("increase"));
}

void CardEditorToolBar::setupConnections() {
  connect(font_family_combobox_, &QComboBox::currentTextChanged, this, &CardEditorToolBar::handleFontFamilyChanged);
}

void CardEditorToolBar::handleFontFamilyChanged(const QString &font_family_name) {
  if(font_family_name == current_card_font_.family()) return;
  this->selected_font_.setFamily(font_family_name);
  emit selectedFontChanged(this->selected_font_);
}

CardEditorToolBar::CardEditorToolBar(QWidget *parent) : QToolBar(parent) {
  setObjectName(QString("card_editor_toolbar"));

  setupGui();
  setupConnections();
}

QFont CardEditorToolBar::selectedFont() {
  return this->selected_font_;
}

void CardEditorToolBar::updateFont(const QFont& font) {
  font_family_combobox_->setCurrentText(font.family());
  font_size_combobox_->setCurrentText(QString::number(font.pointSize()));
  action_bold_->setChecked(font.bold());
  action_italic_->setChecked(font.italic());
  action_underlined_->setChecked(font.underline());
}

