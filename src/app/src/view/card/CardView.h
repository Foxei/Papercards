/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardView.h
 */
#ifndef PAPERCARDS_CARDVIEW_H
#define PAPERCARDS_CARDVIEW_H

#include <QFrame>

class CardView : public QFrame{
  Q_OBJECT
 private:

  void setupGui();

  void setupConnections();

 public:

  explicit CardView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
};

#endif //PAPERCARDS_CARDVIEW_H
