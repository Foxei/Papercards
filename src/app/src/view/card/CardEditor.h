/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.h
 */
#ifndef PAPER_CARDS_CARD_EDITOR_H
#define PAPER_CARDS_CARD_EDITOR_H

#include <QScrollArea>
#include <QWheelEvent>
#include <QPaintEvent>

#include "DualCardView.h"
#include "CardEditorBackground.h"

class CardEditor : public QScrollArea {
 Q_OBJECT
  Q_PROPERTY(qreal scale_factor READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)

 private:

  const QPointF scale_factor_boundaries = QPointF(1.0, 2);

  qreal scale_factor_ = 1.0;

  CardEditorBackground *card_view_background = Q_NULLPTR;
  DualCardView *card_view = Q_NULLPTR;

  void setupGui();

  void setupConnections();

 public:

  explicit CardEditor(QWidget *parent = Q_NULLPTR);

  ~CardEditor() override;

  void wheelEvent(QWheelEvent *event) override;

  qreal scaleFactor() const;

 public slots:

  void setScaleFactor(qreal scale_factor);

 signals:

  void scaleFactorChanged(qreal);

};

#endif //PAPER_CARDS_CARD_EDITOR_H
