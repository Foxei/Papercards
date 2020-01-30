#include "View.h"

#include <controller/Controller.h>

void View::init() {
  connect(Controller::instance(), &Controller::updateCardSize, this, &View::updateCardSize);
  connect(Controller::instance(), &Controller::updateCardElement, this, &View::updateCardElement);
  connect(Controller::instance(), &Controller::showCardElement, this, &View::showCardElement);
  connect(Controller::instance(), &Controller::updateCardElementFont, this, &View::updateCardElementFont);

  connect(this, &View::cardElementUpdated, Controller::instance(), &Controller::updateModelData);
}

void View::free() {

}

void View::showMainWindow(const std::shared_ptr<MainWindow> &main_window) {
  this->main_window_weak_ = std::weak_ptr<MainWindow>(main_window);
  // Check if main window is still live
  if (auto main_window_shared = this->main_window_weak_.lock())
    main_window_shared->show();
  else
    qFatal("Main window is not live to be shown.");
}
