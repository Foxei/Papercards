#ifndef PAPER_CARDS_CONTROLLER_H
#define PAPER_CARDS_CONTROLLER_H

#include <QObject>

class Controller : public QObject {
 Q_OBJECT
 private:
  Controller() = default;
 public:

  static Controller* instance(){
   static Controller controller;
   return &controller;
 }

  void init();

  void connectModelAndView();

  void free();

};

#endif //PAPER_CARDS_CONTROLLER_H
