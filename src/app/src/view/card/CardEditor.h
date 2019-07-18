/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.h
 */
#ifndef PAPERCARDS_CARDEDITOR_H
#define PAPERCARDS_CARDEDITOR_H

#include <QScrollArea>
#include <QWheelEvent>
#include <QSize>
#include <QPointF>
#include <QPageSize>
#include <QPageLayout>
#include <QApplication>
#include <QScreen>

#include "CardView.h"

class CardEditor : public QScrollArea {
 Q_OBJECT
 private:
  QPointF screen_dpi = QPoint(QApplication::primaryScreen()->logicalDotsPerInchX(), QApplication::primaryScreen()->logicalDotsPerInchY());
  QPageSize page_size = QPageSize(QPageSize::definitionSize(QPageSize::A6), QPageSize::Unit::Millimeter);
  QPageLayout::Orientation page_orientation = QPageLayout::Orientation::Landscape;

  QSize base_size = QSize(0,0);
  int page_gap = 10;

  double scale_factor = 1.0;
  QPointF scale_factor_boundaries = QPointF(0.5, 2);

  QWidget* container_widget_cards = Q_NULLPTR;

  CardView* card_view_front = Q_NULLPTR;
  CardView* card_view_back = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 public:

  explicit CardEditor(QWidget *parent = Q_NULLPTR);

  void wheelEvent(QWheelEvent* event) override;

};

#endif //PAPERCARDS_CARDEDITOR_H
