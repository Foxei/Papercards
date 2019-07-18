/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.h
 */
#ifndef PAPERCARDS_CARD_EDITOR_H
#define PAPERCARDS_CARD_EDITOR_H

#include <QScrollArea>
#include <QWheelEvent>

#include "DualCardView.h"

class CardEditor : public QScrollArea {
 Q_OBJECT
 private:

  DualCardView* card_view = Q_NULLPTR;

  QPointF scale_factor_boundaries = QPointF(0.5, 2);

  void setupGui();

  void setupConnections();

 public:

  explicit CardEditor(QWidget *parent = Q_NULLPTR);

  ~CardEditor() override;

  void wheelEvent(QWheelEvent* event) override;

};

#endif //PAPERCARDS_CARD_EDITOR_H
