#include "ScalableLineEdit.h"
#include <QDebug>
#include <QLayout>

void ScalableLineEdit::scale(qreal scale_factor) {
  this->scale_factor_ = scale_factor;
  setBaseFont(base_font_);
  setTextMargins(base_text_margin_);
  setContentsMargins(base_margin_);
  setFixedHeight(base_height_ * scale_factor_);
}

ScalableLineEdit::ScalableLineEdit(QWidget *parent) : QLineEdit(parent) {
  base_font_ = font();
  base_text_margin_ = textMargins();
  base_margin_ = contentsMargins();
  base_height_ = height();
}

void ScalableLineEdit::setBaseFont(const QFont &font) {
  this->base_font_ = font;
  QFont new_font = base_font_;
  new_font.setPointSizeF(new_font.pointSizeF() * scale_factor_ * 1.15);
  QLineEdit::setFont(new_font);
}

void ScalableLineEdit::setTextMargins(int left, int top, int right, int bottom) {
  base_text_margin_ = QMargins(left, top, right, bottom);
  QLineEdit::setTextMargins(static_cast<int>(left * scale_factor_),
                            static_cast<int>(top * scale_factor_),
                            static_cast<int>(right * scale_factor_),
                            static_cast<int>(bottom * scale_factor_));
}

void ScalableLineEdit::setTextMargins(const QMargins &margins) {
  setTextMargins(margins.left(), margins.top(), margins.right(), margins.bottom());
}

void ScalableLineEdit::setContentsMargins(int left, int top, int right, int bottom) {
  base_margin_ = QMargins(left, top, right, bottom);
  QLineEdit::setContentsMargins(static_cast<int>(left * scale_factor_),
                                static_cast<int>(top * scale_factor_),
                                static_cast<int>(right * scale_factor_),
                                static_cast<int>(bottom * scale_factor_));
}

void ScalableLineEdit::setContentsMargins(const QMargins &margins) {
  setContentsMargins(margins.left(), margins.top(), margins.right(), margins.bottom());
}

QFont ScalableLineEdit::baseFont() {
  return base_font_;
}
