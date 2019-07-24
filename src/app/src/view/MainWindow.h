/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file MainWindow.h
 */
#ifndef PAPERCARDS_MAIN_WINDOW_H
#define PAPERCARDS_MAIN_WINDOW_H

#include <QMainWindow>
#include <QFrame>

#include "card/CardEditor.h"
#include "card/CardEditorToolbar.h"
#include "base/StatusBar.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 private:

  CardEditor* card_editor = Q_NULLPTR;
  CardEditorToolbar* card_editor_toolbar = Q_NULLPTR;
  StatusBar* status_bar = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 public:

  explicit MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

  ~MainWindow() override;

};

#endif //PAPERCARDS_MAIN_WINDOW_H
