/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file CardEditorToolbar.h
 */

#ifndef PAPERCARDS_CARD_EDITOR_TOOLBAR_H
#define PAPERCARDS_CARD_EDITOR_TOOLBAR_H

#include <QToolBar>

class CardEditorToolbar : public QToolBar{
 private:

  void setupGui();

  void setupConnections();

 public:
  explicit CardEditorToolbar(QWidget *parent = Q_NULLPTR);
};

#endif //PAPERCARDS_CARD_EDITOR_TOOLBAR_H
