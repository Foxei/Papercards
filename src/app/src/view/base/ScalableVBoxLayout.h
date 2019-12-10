#ifndef SCALABLE_V_BOX_LAYOUT_H
#define SCALABLE_V_BOX_LAYOUT_H

#include <QVBoxLayout>

class ScalableVBoxLayout : public QVBoxLayout {
 Q_OBJECT
 private:
  qreal scale_factor_ = 1.0;
  int base_spacing_ = 0;
  int base_margin_ = 0;

 public slots:
  void scale(qreal scale_factor);

 public:
  explicit ScalableVBoxLayout(QWidget *parent = nullptr);

  void setSpacing(int spacing);

  void setMargin(int margin);

};

#endif //SCALABLE_V_BOX_LAYOUT_H
