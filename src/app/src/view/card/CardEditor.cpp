/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.cpp
 */

#include "CardEditor.h"

#include <QHBoxLayout>
#include <QScrollBar>

#include <QSettings>
#include <QPainter>
#include <QBrush>
#include <QDebug>

void CardEditor::setupGui() {


  setWidgetResizable(true);

  card_view_background = new CardEditorBackground(this);
  auto* parent_layout = new QHBoxLayout(card_view_background);

  card_view = new DualCardView(this);

  parent_layout->addStretch();
  parent_layout->addWidget(card_view, 0, Qt::AlignCenter);
  parent_layout->addStretch();
  parent_layout->setMargin(0);
  card_view_background->setLayout(parent_layout);

  setWidget(card_view_background);
  setAutoFillBackground(true);
}

void CardEditor::setupConnections() {
  connect(this, &CardEditor::setScaleFactor, card_view, &DualCardView::setScaleFactor);
  connect(card_view, &DualCardView::scaleFactorChanged, this, &CardEditor::scaleFactorChanged);
}

CardEditor::CardEditor(QWidget *parent) : QScrollArea(parent) {
  setObjectName(QString("card_editor"));

  setupGui();
  setupConnections();
}

CardEditor::~CardEditor() {
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Papercards", "Editor");
  settings.setValue("scale_factor",card_view->scaleFactor());
}

void CardEditor::wheelEvent(QWheelEvent* event) {
  QScrollArea::wheelEvent(event);
  if(!(event->modifiers() & Qt::ControlModifier))
    return;
  if(event->modifiers() & Qt::AltModifier)
    return;
  if(event->modifiers() & Qt::ShiftModifier)
    return;

  double scroll_direction= event->angleDelta().y() / abs(event->angleDelta().y());
  double scrolled_factor = scroll_direction*0.1;
  double scale_factor = card_view->scaleFactor();
  double new_scale_factor = scale_factor + scrolled_factor;

  if(new_scale_factor>scale_factor_boundaries.y())
    new_scale_factor = scale_factor_boundaries.y();
  else if(new_scale_factor<scale_factor_boundaries.x())
    new_scale_factor = scale_factor_boundaries.x();

  card_view->setScaleFactor(new_scale_factor);

  QPoint new_event_pos = event->pos()*new_scale_factor;
  ensureVisible(new_event_pos.x(),new_event_pos.y(),0,0);

  event->accept();
}
