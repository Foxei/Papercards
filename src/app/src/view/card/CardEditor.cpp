/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.cpp
 */

#include "CardEditor.h"

#include <QHBoxLayout>
#include <QScrollBar>

#include <QDebug>

void CardEditor::setupGui() {
  setWidgetResizable(true);

  auto* parent_widget = new QWidget(this);
  auto* parent_layout = new QHBoxLayout(parent_widget);

  card_view = new CardView(this);

  parent_layout->addStretch();
  parent_layout->addWidget(card_view, Qt::AlignCenter);
  parent_layout->addStretch();
  parent_layout->setMargin(0);
  parent_widget->setLayout(parent_layout);

  setWidget(parent_widget);
}

void CardEditor::setupConnections() {

}

CardEditor::CardEditor(QWidget *parent) : QScrollArea(parent) {
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
  double scale_factor = card_view->scaleFactor();
  double new_scale_factor = scale_factor + scrolled_factor;

  if(new_scale_factor>scale_factor_boundaries.y()){
    new_scale_factor = scale_factor_boundaries.y();
    scrolled_factor = 0;
  }else if(new_scale_factor<scale_factor_boundaries.x()){
    new_scale_factor = scale_factor_boundaries.x();
    scrolled_factor = 0;
  }

  QPoint new_event_pos = event->pos()*(1+scrolled_factor);

  card_view->setScaleFactor(new_scale_factor);

  ensureVisible(new_event_pos.x(), new_event_pos.y(), 100,100);

  event->accept();
}
