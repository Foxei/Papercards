#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include "QWidget"

namespace Ui {
class sidePanel;
}

class SidePanel : public QWidget {
  Q_OBJECT
 private:
  Ui::sidePanel *ui;

 public:
  explicit SidePanel(QWidget *parent = nullptr);
  ~SidePanel() override;
};

#endif //SIDE_PANEL_H
