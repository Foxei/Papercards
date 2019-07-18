/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.cpp
 */

#include "CardEditor.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>

#include <QDebug>

void CardEditor::setupGui() {
  setWidgetResizable(true);

  auto* parent_widget = new QWidget(this);
  auto* parent_layout = new QHBoxLayout(parent_widget);

  container_widget_cards = new QWidget(this);
  auto* layout = new QVBoxLayout(container_widget_cards);

  card_view_front = new CardView(container_widget_cards);
  card_view_back = new CardView(container_widget_cards);

  layout->addWidget(card_view_front);
  layout->addWidget(card_view_back);
  layout->setMargin(0);
  layout->setSpacing(page_gap);
  container_widget_cards->setLayout(layout);

  parent_layout->addStretch();
  parent_layout->addWidget(container_widget_cards, Qt::AlignCenter);
  parent_layout->addStretch();
  parent_layout->setMargin(0);
  parent_widget->setLayout(parent_layout);

  setWidget(parent_widget);
  container_widget_cards->setMinimumSize(base_size*scale_factor);
  container_widget_cards->setMaximumSize(base_size*scale_factor);
}

void CardEditor::setupConnections() {

}

CardEditor::CardEditor(QWidget *parent) : QScrollArea(parent) {
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

void CardEditor::wheelEvent(QWheelEvent* event) {
  QScrollArea::wheelEvent(event);
  if(!(event->modifiers() & Qt::ControlModifier))
    return;
  if(event->modifiers() & Qt::AltModifier)
    return;
  if(event->modifiers() & Qt::ShiftModifier)
    return;

  double scroll_degrees = event->angleDelta().y() / 8.0;
  double scrolled_factor = scroll_degrees / 360.0;
  double new_scale_factor = scale_factor + scrolled_factor;

  if(new_scale_factor>scale_factor_boundaries.y()){
    new_scale_factor = scale_factor_boundaries.y();
    scrolled_factor = 0;
  }else if(new_scale_factor<scale_factor_boundaries.x()){
    new_scale_factor = scale_factor_boundaries.x();
    scrolled_factor = 0;
  }

  QPoint new_event_pos = event->pos()*(1+scrolled_factor);

  container_widget_cards->setMinimumSize(base_size*new_scale_factor);
  container_widget_cards->setMaximumSize(base_size*new_scale_factor);

  ensureVisible(new_event_pos.x(), new_event_pos.y(), 100,100);

  scale_factor = new_scale_factor;
  event->accept();
}
