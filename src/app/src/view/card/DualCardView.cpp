/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardView.cpp
 */

#include "DualCardView.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QToolTip>

void DualCardView::setupGui() {
  auto* layout = new QVBoxLayout(container_widget_cards_);

  card_view_front_ = new CardView(Card::Site::FRONT, container_widget_cards_);
  card_view_back_ = new CardView(Card::Site::BACK, container_widget_cards_);

  layout->addWidget(card_view_front_);
  layout->addWidget(card_view_back_);
  layout->setMargin(page_gap_);
  layout->setSpacing(page_gap_);
  setLayout(layout);

  card_view_front_->setFixedSize(card_size_*scale_factor_);
  card_view_back_->setFixedSize(card_size_*scale_factor_);
  //setFixedSize(base_size*m_scale_factor);
}

void DualCardView::setupConnections() {
  connect(this, &DualCardView::scaleFactorChanged, this, &DualCardView::scaleCards);
  connect(this, &DualCardView::scaleFactorChanged, card_view_front_, &CardView::scaleCards);
  connect(this, &DualCardView::scaleFactorChanged, card_view_back_, &CardView::scaleCards);
  connect(this, &DualCardView::showCard, card_view_back_, &CardView::showCard);
  connect(this, &DualCardView::showCard, card_view_front_, &CardView::showCard);
}

void DualCardView::scaleCards(qreal scale_factor) {
  card_view_front_->setFixedSize(card_size_*scale_factor_);
  card_view_back_->setFixedSize(card_size_*scale_factor_);
  //setFixedSize(base_size*m_scale_factor);
}

DualCardView::DualCardView(QWidget *parent, Qt::WindowFlags flags) : QWidget(parent,
                                                                     flags) {
  setObjectName(QString("dual_card_view"));

  QSizeF page_size_inches = page_size_.size(QPageSize::Unit::Inch);
  int pixel_width = static_cast<int>(page_size_inches.width()*screen_dpi_.x());
  int pixel_height = static_cast<int>(page_size_inches.height()*screen_dpi_.y());
  if(page_orientation_ == QPageLayout::Orientation::Portrait) {
    card_size_ = QSize(pixel_width, pixel_height);
  }else{ // Landscape
    card_size_ = QSize(pixel_height, pixel_width);
  }

  setupGui();
  setupConnections();
}

void DualCardView::setScaleFactor(qreal scale_factor) {
  scale_factor_ = scale_factor;
  emit scaleFactorChanged(scale_factor);
}

qreal DualCardView::scaleFactor() const {
  return scale_factor_;
}

QPoint DualCardView::positionBackCard() const {
  return mapToParent(card_view_back_->pos());
}

QPoint DualCardView::positionFrontCard() const {
  return mapToParent(card_view_front_->pos());
}
