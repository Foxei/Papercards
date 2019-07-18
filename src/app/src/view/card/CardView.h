/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardView.h
 */
#ifndef PAPERCARDS_CARD_VIEW_H
#define PAPERCARDS_CARD_VIEW_H

#include <QFrame>
#include <QSize>
#include <QPointF>
#include <QPageSize>
#include <QPageLayout>
#include <QApplication>
#include <QScreen>

class CardView : public QFrame{
  Q_OBJECT

 private:

  QPointF screen_dpi = QPointF(QApplication::primaryScreen()->logicalDotsPerInchX(), QApplication::primaryScreen()->logicalDotsPerInchY());
  QPageSize page_size = QPageSize(QPageSize::definitionSize(QPageSize::A6), QPageSize::Unit::Millimeter);
  QPageLayout::Orientation page_orientation = QPageLayout::Orientation::Landscape;

  QSize base_size = QSize(0,0);
  int page_gap = 10;

  qreal m_scale_factor = 1.0;

  QWidget* container_widget_cards = Q_NULLPTR;

  CardView* card_view_front = Q_NULLPTR;
  CardView* card_view_back = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 public:

  explicit CardView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

  void setScaleFactor(qreal scale_factor);
  qreal scaleFactor() const;

  signals:

  void scaleFactorChanged(qreal);
};

#endif //PAPERCARDS_CARD_VIEW_H
