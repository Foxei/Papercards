/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file MainWindow.h
 */
#ifndef PAPERCARDS_MAIN_WINDOW_H
#define PAPERCARDS_MAIN_WINDOW_H

#include <QMainWindow>
#include <QFrame>

#include "src/view/card/CardEditor.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 private:

  CardEditor* container_card = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 public:

  explicit MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

  ~MainWindow() override;

};

#endif //PAPERCARDS_MAIN_WINDOW_H
