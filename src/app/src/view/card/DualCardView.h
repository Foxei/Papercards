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
  //@formatter:on

 private:
  qreal scale_factor_ = 1.0; ///< Scale factor for this view

  QPointF screen_dpi_ =
      QPointF(QApplication::primaryScreen()->logicalDotsPerInchX(),
              QApplication::primaryScreen()->logicalDotsPerInchY());

  QSize card_size_ = QSize(0, 0);
  int page_gap_ = 10;

  QWidget *container_widget_cards_ = Q_NULLPTR;

  CardView *card_view_front_ = Q_NULLPTR;
  CardView *card_view_back_ = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 private slots:

  void scaleCards(qreal scale_factor);

 public:

  explicit DualCardView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

  qreal scaleFactor() const;

 public slots:

  void setScaleFactor(qreal scale_factor);

  void updateCardElement(bool front, const QString &field_name, const QVariant &field_content);

  void updateCardElementFont(bool front, const QString &field_name, const QFont &field_content);

  void showCardElement(bool front, const QString &field_name, bool visible);

  void updateCardSize(QSizeF card_size, QPageLayout::Orientation card_orientation);

 signals:

  void scaleFactorChanged(qreal);

  void updateFrontCardElement(QString field_name, QVariant field_content);

  void updateFrontCardElementFont(QString field_name, QFont field_font);

  void showFrontCardElement(QString field_name, bool visible);

  void updateBackCardElement(QString field_name, QVariant field_content);

  void updateBackCardElementFont(QString field_name, QFont field_font);

  void showBackCardElement(QString field_name, bool visible);

  void cardElementUpdated(bool front, const QString &field_name, const QVariant &field_content);

};

#endif //PAPER_CARDS_DUAL_CARD_VIEW_H
