#include "ScalableTextEdit.h"

#include <QLayout>
#include <QDebug>
#include <QMargins>

ScalableTextEdit::ScalableTextEdit(QWidget *parent) : QTextEdit(parent) {
  // Copy base values from current values.
  this->base_font_ = font();
  this->base_margins_ = contentsMargins();

  // Set fix document margins to
  document()->setDocumentMargin(2);
  setAutoFormatting(AutoFormattingFlag::AutoAll);
}

void ScalableTextEdit::wheelEvent(QWheelEvent *event) {
  // Cancel the wheels event to prevent the scroll pane from working.
}

void ScalableTextEdit::setBaseFont(const QFont &font) {
  const double CORRECTION_FACTOR = 1.15;

  this->base_font_ = font;
  QFont scaled_font = this->base_font_;
  scaled_font.setPointSizeF(scaled_font.pointSizeF() * this->scale_factor_ * CORRECTION_FACTOR);
  QTextEdit::setFont(scaled_font);

  emit baseFontChanged(this->base_font_);
}

void ScalableTextEdit::setScaleFactor(qreal scale_factor) {
  this->scale_factor_ = scale_factor;
  setBaseFont(this->base_font_);
  setBaseMargins(this->base_margins_);

  emit scaleFactorChanged(this->scale_factor_);
}

void ScalableTextEdit::setBaseMargins(const QMargins &margins) {
  this->base_margins_ = margins;
  QTextEdit::setContentsMargins(margins * this->scale_factor_);

  emit baseMarginsChanged(this->base_margins_);
}

QFont ScalableTextEdit::baseFont() { return this->base_font_; }

qreal ScalableTextEdit::scaleFactor() { return this->scale_factor_; }

QMargins ScalableTextEdit::baseMargins() { return this->base_margins_; }