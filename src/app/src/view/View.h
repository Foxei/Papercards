#ifndef PAPER_CARDS_VIEW_H
#define PAPER_CARDS_VIEW_H

#include <QObject>
#include <QApplication>

#include <memory>

#include "view/MainWindow.h"

#include "model/Card.h"

class View : public QObject {
 Q_OBJECT

 private:

  std::weak_ptr<MainWindow> main_window_weak_;

  View() = default;

 public:
  static View* instance(){
    static View view;
    return &view;
  }

  void init();

  void showMainWindow(const std::shared_ptr<MainWindow>& main_window);

  void free();

 signals:

  void showCardInEditor(Card* card);
};

#endif //PAPER_CARDS_VIEW_H
