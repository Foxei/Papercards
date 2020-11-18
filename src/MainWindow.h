#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
  class mainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  Ui::mainWindow *ui;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
};

#endif // MAIN_WINDOW_H
