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
  //@formatter:off
  Q_OBJECT
  Q_PROPERTY(qreal scale_factor_ READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)
  Q_PROPERTY(Card* current_card READ currentCard WRITE setCurrentCard NOTIFY currentCardChanged)
  //@formatter:on

 private:
  qreal scale_factor_ = 1.0; ///< Scale factor for this view
  Card *current_card = nullptr; ///< Pointer to card that us displayed in the moment


  QPointF screen_dpi_ =
      QPointF(QApplication::primaryScreen()->logicalDotsPerInchX(),
              QApplication::primaryScreen()->logicalDotsPerInchY());
  QPageSize page_size_ = QPageSize(QPageSize::PageSizeId::A6);

  QSize card_size_ = QSize(0, 0);
  int page_gap_ = 10;


  QWidget *container_widget_cards_ = Q_NULLPTR;

  CardView *card_view_front_ = Q_NULLPTR;
  CardView *card_view_back_ = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 private slots:

  void scaleCards(qreal scale_factor);

  void updateSizes(Card *card);

 public:

  explicit DualCardView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

  qreal scaleFactor() const;

  Card *currentCard() const;

 public slots:

  void setScaleFactor(qreal scale_factor);

  void setCurrentCard(Card *card);

 signals:

  void scaleFactorChanged(qreal);

  void currentCardChanged(Card *);

};

#endif //PAPER_CARDS_DUAL_CARD_VIEW_H
