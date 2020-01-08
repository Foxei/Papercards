/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardView.h
 */
#ifndef PAPER_CARDS_DUAL_CARD_VIEW_H
#define PAPER_CARDS_DUAL_CARD_VIEW_H

#include <QFrame>
#include <QSize>
#include <QPointF>
#include <QPageSize>
#include <QPageLayout>
#include <QApplication>
#include <QScreen>

#include "CardView.h"

class DualCardView : public QWidget {
 Q_OBJECT
 Q_PROPERTY(qreal scale_factor READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)

 private:

  QPointF screen_dpi_ =
      QPointF(QApplication::primaryScreen()->logicalDotsPerInchX(),
              QApplication::primaryScreen()->logicalDotsPerInchY());
  QPageSize page_size_ = QPageSize(QPageSize::definitionSize(QPageSize::A6),
                                   QPageSize::Unit::Millimeter);
  QPageLayout::Orientation
      page_orientation_ = QPageLayout::Orientation::Landscape;

  QSize card_size_ = QSize(0, 0);
  int page_gap_ = 10;

  qreal scale_factor_ = 1.0;

  QWidget *container_widget_cards_ = Q_NULLPTR;

  CardView *card_view_front_ = Q_NULLPTR;
  CardView *card_view_back_ = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 private slots:

  void scaleCards(qreal scale_factor);

 public:

  explicit DualCardView(QWidget *parent = Q_NULLPTR,
                        Qt::WindowFlags flags = Qt::WindowFlags());

  qreal scaleFactor() const;

  QPoint positionFrontCard() const;

  QPoint positionBackCard() const;

 public slots:

  void setScaleFactor(qreal scale_factor);

 signals:

  void scaleFactorChanged(qreal);

  void showCard(Card* card);

};

#endif //PAPER_CARDS_DUAL_CARD_VIEW_H
