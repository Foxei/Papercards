/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file CardEditorToolbar.h
 */

#ifndef PAPER_CARDS_CARD_EDITOR_TOOLBAR_H
#define PAPER_CARDS_CARD_EDITOR_TOOLBAR_H

#include <QToolBar>
#include <QComboBox>

class CardEditorToolBar : public QToolBar {
 private:

  QComboBox *font_family_combobox_ = Q_NULLPTR;
  QComboBox *font_size_combobox_ = Q_NULLPTR;

  QAction* action_bold_ = Q_NULLPTR;
  QAction* action_italic_ = Q_NULLPTR;
  QAction* action_underlined_ = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 public:
  explicit CardEditorToolBar(QWidget *parent = Q_NULLPTR);

 public slots:

  void updateFont(const QFont& font);
};

#endif //PAPER_CARDS_CARD_EDITOR_TOOLBAR_H
