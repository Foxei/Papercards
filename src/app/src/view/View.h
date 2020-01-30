#ifndef PAPER_CARDS_VIEW_H
#define PAPER_CARDS_VIEW_H

#include <QObject>
#include <QApplication>
#include <QPointer>

#include <memory>

#include "view/MainWindow.h"

class View : public QObject {
 Q_OBJECT

 private:

  std::weak_ptr<MainWindow> main_window_weak_;

  QPointer<CardEditor> card_editor = Q_NULLPTR;
  QPointer<DualCardView> dual_card_view = Q_NULLPTR;

  View() = default;

 public:
  static View *instance() {
    static View view;
    return &view;
  }

  void init();

  void showMainWindow(const std::shared_ptr<MainWindow> &main_window);

  void free();

 signals:

  void showCardElement(bool front, const QString &field_name, bool visible);

  void updateCardElement(bool front, const QString &field_name, const QVariant &field_content);

  void updateCardElementFont(bool front, const QString &field_name, const QFont &field_font);

  void updateCardSize(QSizeF card_size, QPageLayout::Orientation card_orientation);

  void cardElementUpdated(bool front, const QString &field_name, const QVariant &field_content);

};

#endif //PAPER_CARDS_VIEW_H
