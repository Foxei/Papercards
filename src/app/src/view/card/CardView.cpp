/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardView.cpp
 */

#include "CardView.h"

#include <QVBoxLayout>

void CardView::setupGui() {
  container_widget_cards = new QWidget(this);
  auto* layout = new QVBoxLayout(container_widget_cards);

  card_view_front = new CardView(container_widget_cards);
  card_view_back = new CardView(container_widget_cards);

  layout->addWidget(card_view_front);
  layout->addWidget(card_view_back);
  layout->setMargin(0);
  layout->setSpacing(page_gap);
  container_widget_cards->setLayout(layout);

  container_widget_cards->setMinimumSize(base_size*m_scale_factor);
  container_widget_cards->setMaximumSize(base_size*m_scale_factor);
}

void CardView::setupConnections() {

}

CardView::CardView(QWidget *parent, Qt::WindowFlags flags) : QFrame(parent,
                                                                     flags) {
  QSizeF page_size_inches = page_size.size(QPageSize::Unit::Inch);
  int pixel_width = static_cast<int>(page_size_inches.width()*screen_dpi.x());
  int pixel_height = static_cast<int>(page_size_inches.height()*screen_dpi.y());
  if(page_orientation == QPageLayout::Orientation::Portrait)
    base_size = QSize(pixel_width, pixel_height*2+page_gap);
  else{ // Landscape
    base_size = QSize(pixel_height, pixel_width*2+page_gap);
  }

  setupGui();
  setupConnections();
}

void CardView::setScaleFactor(qreal scale_factor) {
  m_scale_factor = scale_factor;
  emit scaleFactorChanged(scale_factor);
}

qreal CardView::scaleFactor() const {
  return m_scale_factor;
}

