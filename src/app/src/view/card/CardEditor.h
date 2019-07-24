/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.h
 */
#ifndef PAPERCARDS_CARD_EDITOR_H
#define PAPERCARDS_CARD_EDITOR_H

#include <QScrollArea>
#include <QWheelEvent>
#include <QPaintEvent>

#include "DualCardView.h"
#include "CardEditorBackground.h"

class CardEditor : public QScrollArea {
 Q_OBJECT
 private:

  CardEditorBackground* card_view_background = Q_NULLPTR;
  DualCardView* card_view = Q_NULLPTR;

  QPointF scale_factor_boundaries = QPointF(0.5, 2);

  void setupGui();

  void setupConnections();

 public:

  explicit CardEditor(QWidget *parent = Q_NULLPTR);

  ~CardEditor() override;

  void wheelEvent(QWheelEvent* event) override;

 signals:
  void setScaleFactor(qreal);
  void scaleFactorChanged(qreal);

};

#endif //PAPERCARDS_CARD_EDITOR_H
