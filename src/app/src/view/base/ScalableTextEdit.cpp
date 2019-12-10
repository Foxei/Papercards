#include "ScalableTextEdit.h"

#include <QLayout>
#include <QDebug>
#include <QMargins>

void ScalableTextEdit::scale(qreal scale_factor) {
  this->scale_factor_ = scale_factor;
  zoomIn();
  setBaseFont(base_font_);
  setContentsMargins(base_margin_);
}

ScalableTextEdit::ScalableTextEdit(QWidget *parent) : QTextEdit(parent) {
  base_font_ = font();
  base_margin_ = contentsMargins();
  document()->setDocumentMargin(2);
  setAutoFormatting(AutoFormattingFlag::AutoAll);
}

void ScalableTextEdit::setBaseFont(const QFont &font) {
  this->base_font_ = font;
  QFont new_font = base_font_;
  new_font.setPointSizeF(new_font.pointSizeF() * scale_factor_ * 1.15);
  QTextEdit::setFont(new_font);
}

void ScalableTextEdit::setContentsMargins(int left, int top, int right, int bottom) {
  base_margin_ = QMargins(left, top, right, bottom);
  QTextEdit::setContentsMargins(static_cast<int>(left * scale_factor_),
                            static_cast<int>(top * scale_factor_),
                            static_cast<int>(right * scale_factor_),
                            static_cast<int>(bottom * scale_factor_));
}

void ScalableTextEdit::setContentsMargins(const QMargins &margins) {
  setContentsMargins(margins.left(),margins.top(),margins.right(),margins.bottom());
}

QFont ScalableTextEdit::baseFont() {
  return base_font_;
}
