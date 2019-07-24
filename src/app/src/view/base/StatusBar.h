/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file StatusBar.h
 */
#ifndef PAPERCARDS_STATUSBAR_H
#define PAPERCARDS_STATUSBAR_H

#include <QStatusBar>

class StatusBar : public QStatusBar {
 Q_OBJECT
 private:

  void setupGui();

  void setupConnections();

 public:

  explicit StatusBar(QWidget *parent = Q_NULLPTR);

};

#endif //PAPERCARDS_STATUSBAR_H
