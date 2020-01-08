#include "View.h"

void View::init() {

}

void View::showMainWindow(const std::shared_ptr<MainWindow>& main_window) {
  this->main_window_weak_ = std::weak_ptr<MainWindow>(main_window);
  // Check if main window is still live
  if(auto main_window_shared = this->main_window_weak_.lock())
    main_window_shared->show();
  else qFatal("Main window is not live to be shown.");

  if(auto default_card_shared = Model::instance()->defaultCard().lock()) {
    qInfo("Emit signal to show default card in editor.");
    emit showCardInEditor(default_card_shared.get());
  }
  else qFatal("Models default card is not live to be shown.");

}

void View::free() {

}
