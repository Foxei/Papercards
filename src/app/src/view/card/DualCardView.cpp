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
  auto *layout = new QVBoxLayout(container_widget_cards_);

  card_view_front_ = new CardView(true, container_widget_cards_);
  card_view_back_ = new CardView(false, container_widget_cards_);

  layout->addWidget(card_view_front_);
  layout->addWidget(card_view_back_);
  layout->setMargin(page_gap_);
  layout->setSpacing(page_gap_);
  setLayout(layout);

  card_view_front_->setFixedSize(card_size_ * scale_factor_);
  card_view_back_->setFixedSize(card_size_ * scale_factor_);
  //setFixedSize(base_size*m_scale_factor);
}

void DualCardView::updateCardSize(QSizeF card_size, QPageLayout::Orientation card_orientation) {
  //QSizeF page_size_inches = card->size().size(QPageSize::Unit::Inch);
  int pixel_width = static_cast<int>(card_size.width() * screen_dpi_.x());
  int pixel_height = static_cast<int>(card_size.height() * screen_dpi_.y());

  if (card_orientation == QPageLayout::Orientation::Portrait) {
    card_size_ = QSize(pixel_width, pixel_height);
  } else { // Landscape
    card_size_ = QSize(pixel_height, pixel_width);
  }
  card_view_front_->setFixedSize(card_size_ * scale_factor_);
  card_view_front_->updateBaseContentSize();
  card_view_back_->setFixedSize(card_size_ * scale_factor_);
  card_view_back_->updateBaseContentSize();


//  this->base_content_size = content_text_edit_->size() / this->scale_factor_;

}

void DualCardView::setupConnections() {
  connect(this, &DualCardView::scaleFactorChanged, this, &DualCardView::scaleCards);
  connect(this, &DualCardView::scaleFactorChanged, card_view_front_, &CardView::setScaleFactor);
  connect(this, &DualCardView::scaleFactorChanged, card_view_back_, &CardView::setScaleFactor);

  connect(this, &DualCardView::updateBackCardElement, card_view_back_, &CardView::updateCardElement);
  connect(this, &DualCardView::updateFrontCardElement, card_view_front_, &CardView::updateCardElement);

  connect(this, &DualCardView::showBackCardElement, card_view_back_, &CardView::showCardElement);
  connect(this, &DualCardView::showFrontCardElement, card_view_front_, &CardView::showCardElement);

  connect(this, &DualCardView::updateBackCardElementFont, card_view_back_, &CardView::updateCardElementFont);
  connect(this, &DualCardView::updateFrontCardElementFont, card_view_front_, &CardView::updateCardElementFont);

  connect(card_view_front_,
          &CardView::cardElementUpdated,
          [this](const QString &field_name, const QVariant &field_content) {
            emit cardElementUpdated(true, field_name, field_content);
          });
  connect(card_view_back_,
          &CardView::cardElementUpdated,
          [this](const QString &field_name, const QVariant &field_content) {
            emit cardElementUpdated(false, field_name, field_content);
          });
}

void DualCardView::scaleCards(qreal scale_factor) {
  card_view_front_->setFixedSize(card_size_ * scale_factor_);
  card_view_back_->setFixedSize(card_size_ * scale_factor_);
}

DualCardView::DualCardView(QWidget *parent, Qt::WindowFlags flags) : QWidget(parent, flags) {
  setObjectName(QString("dual_card_view"));

  setupGui();
  setupConnections();
}

void DualCardView::setScaleFactor(qreal scale_factor) {
  if (this->scale_factor_ == scale_factor) return;

  scale_factor_ = scale_factor;
  emit scaleFactorChanged(scale_factor);
}

void DualCardView::updateCardElement(bool front, const QString &field_name, const QVariant &field_content) {
  if (front) {
    emit updateFrontCardElement(field_name, field_content);
  } else {
    emit updateBackCardElement(field_name, field_content);
  }
}

void DualCardView::updateCardElementFont(bool front, const QString &field_name, const QFont &field_font) {
  if (front) {
    emit updateFrontCardElementFont(field_name, field_font);
  } else {
    emit updateBackCardElementFont(field_name, field_font);
  }
}

void DualCardView::showCardElement(bool front, const QString &field_name, bool visible) {
  if (front) {
    emit showFrontCardElement(field_name, visible);
  } else {
    emit showBackCardElement(field_name, visible);
  }
}

qreal DualCardView::scaleFactor() const {
  return scale_factor_;
}

