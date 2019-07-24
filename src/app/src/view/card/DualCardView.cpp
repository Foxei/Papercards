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
  auto* layout = new QVBoxLayout(container_widget_cards);

  card_view_front = new QFrame(container_widget_cards);
  card_view_back = new QFrame(container_widget_cards);

  layout->addWidget(card_view_front);
  layout->addWidget(card_view_back);
  layout->setMargin(page_gap);
  layout->setSpacing(page_gap);
  setLayout(layout);

  card_view_front->setFixedSize(card_size*m_scale_factor);
  card_view_back->setFixedSize(card_size*m_scale_factor);
  //setFixedSize(base_size*m_scale_factor);
}

void DualCardView::setupConnections() {
  connect(this, &DualCardView::scaleFactorChanged, this, &DualCardView::scaleCards);
}

void DualCardView::scaleCards(qreal scale_factor) {
  card_view_front->setFixedSize(card_size*m_scale_factor);
  card_view_back->setFixedSize(card_size*m_scale_factor);
  //setFixedSize(base_size*m_scale_factor);
}

DualCardView::DualCardView(QWidget *parent, Qt::WindowFlags flags) : QWidget(parent,
                                                                     flags) {
  setObjectName(QString("dual_card_view"));

  QSizeF page_size_inches = page_size.size(QPageSize::Unit::Inch);
  int pixel_width = static_cast<int>(page_size_inches.width()*screen_dpi.x());
  int pixel_height = static_cast<int>(page_size_inches.height()*screen_dpi.y());
  if(page_orientation == QPageLayout::Orientation::Portrait) {
    base_size = QSize(pixel_width, 2*pixel_height + 3*page_gap);
    card_size = QSize(pixel_width, pixel_height);
  }else{ // Landscape
    base_size = QSize(pixel_height, 2*pixel_width + 3*page_gap);
    card_size = QSize(pixel_height, pixel_width);
  }

  setupGui();
  setupConnections();
}

void DualCardView::setScaleFactor(qreal scale_factor) {
  m_scale_factor = scale_factor;
  emit scaleFactorChanged(scale_factor);
}

qreal DualCardView::scaleFactor() const {
  return m_scale_factor;
}

QPoint DualCardView::positionBackCard() const {
  return mapToParent(card_view_back->pos());
}

QPoint DualCardView::positionFrontCard() const {
  return mapToParent(card_view_front->pos());
}
