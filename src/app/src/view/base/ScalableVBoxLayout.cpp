#include "ScalableVBoxLayout.h"

void ScalableVBoxLayout::scale(qreal scale_factor) {
  this->scale_factor_ = scale_factor;
  setSpacing(base_spacing_);
  setMargin(base_margin_);
}

ScalableVBoxLayout::ScalableVBoxLayout(QWidget *parent) : QVBoxLayout(parent) {
  base_margin_ = contentsMargins().bottom();
  base_spacing_ = spacing();
}

void ScalableVBoxLayout::setSpacing(int spacing) {
  base_spacing_ = spacing;
  QBoxLayout::setSpacing(static_cast<int>(base_spacing_ * scale_factor_));
}

void ScalableVBoxLayout::setMargin(int margin) {
  base_margin_ = margin;
  QBoxLayout::setMargin(static_cast<int>(base_margin_ * scale_factor_));
}
