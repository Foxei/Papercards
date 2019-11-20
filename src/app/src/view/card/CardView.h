#ifndef PAPER_CARDS_CARD_VIEW_H
#define PAPER_CARDS_CARD_VIEW_H

#include <QFrame>
#include <QPageSize>
#include <QPageLayout>

class CardView : public QFrame {
  Q_OBJECT
 private:
  QPageSize page_size_ = QPageSize(QPageSize::definitionSize(QPageSize::A6),
                                   QPageSize::Unit::Millimeter);
  QPageLayout::Orientation
      page_orientation_ = QPageLayout::Orientation::Landscape;

  void setupGui();

  void setupConnections();

 public:

  explicit CardView(QWidget* parent = Q_NULLPTR);

};

#endif //PAPER_CARDS_CARD_VIEW_H
