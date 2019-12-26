/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file CardEditorToolbar.h
 */

#ifndef PAPER_CARDS_CARD_EDITOR_TOOLBAR_H
#define PAPER_CARDS_CARD_EDITOR_TOOLBAR_H

#include <QToolBar>
#include <QComboBox>
#include <QAction>

class CardEditorToolBar : public QToolBar {
  Q_PROPERTY(QFont selected_font_ READ selectedFont NOTIFY selectedFontChanged)

 private:
  QFont selected_font_;
  QFont current_card_font_;

  QComboBox *font_family_combobox_ = Q_NULLPTR;
  QComboBox *font_size_combobox_ = Q_NULLPTR;

  QAction* action_bold_ = Q_NULLPTR;
  QAction* action_italic_ = Q_NULLPTR;
  QAction* action_underlined_ = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 private slots:
  void handleFontFamilyChanged(const QString &font_family_name);

 public:
  explicit CardEditorToolBar(QWidget *parent = Q_NULLPTR);

  QFont selectedFont();

 public slots:

  void updateFont(const QFont& font);

 signals:
  void selectedFontChanged(QFont);
};

#endif //PAPER_CARDS_CARD_EDITOR_TOOLBAR_H
