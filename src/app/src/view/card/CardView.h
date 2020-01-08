#ifndef PAPER_CARDS_CARD_VIEW_H
#define PAPER_CARDS_CARD_VIEW_H

#include "view/base/ScalableVBoxLayout.h"
#include "view/base/ScalableLineEdit.h"
#include "view/base/ScalableTextEdit.h"

#include "model/Model.h"

#include <QFrame>
#include <QPageSize>
#include <QLineEdit>
#include <QTextEdit>
#include <QPageLayout>

class CardView : public QFrame {
 Q_OBJECT
 private:
  QPageSize page_size_ = QPageSize(QPageSize::definitionSize(QPageSize::A6),
                                   QPageSize::Unit::Millimeter);
  QPageLayout::Orientation
      page_orientation_ = QPageLayout::Orientation::Landscape;

  qreal scale_factor_ = 1.0;

  ScalableVBoxLayout *content_layout_ = nullptr;
  ScalableLineEdit *title_text_edit_ = nullptr;
  ScalableTextEdit *content_text_edit_ = nullptr;

  Card::Site site_;

 public slots:

  void scaleCards(qreal scale_factor);

  void showCard(Card* card);

 private:

  void setupGui();

  void setupConnections();

 public:

  explicit CardView(Card::Site site, QWidget *parent = Q_NULLPTR);
};

#endif //PAPER_CARDS_CARD_VIEW_H
