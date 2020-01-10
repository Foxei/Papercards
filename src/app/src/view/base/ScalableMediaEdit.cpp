#include "ScalableMediaEdit.h"

#include <QLayout>
#include <QDebug>
#include <QMargins>

ScalableMediaEdit::ScalableMediaEdit(QWidget *parent) : QLabel(parent) {
  // Copy base values from current values.
  this->base_size_ = size();
  this->base_margins_ = contentsMargins();
}

void ScalableMediaEdit::setBaseSize(const QSize &size) {
  this->base_size_ = size;
  emit baseSizeChanged(this->base_size_);
}

void ScalableMediaEdit::setBaseFont(const QFont &font) {
  const double CORRECTION_FACTOR = 1.15;

  this->base_font_ = font;
  QFont scaled_font = this->base_font_;
  scaled_font.setPointSizeF(scaled_font.pointSizeF() * this->scale_factor_ * CORRECTION_FACTOR);
  QLabel::setFont(scaled_font);

  emit baseFontChanged(this->base_font_);
}

void ScalableMediaEdit::setScaleFactor(qreal scale_factor) {
  this->scale_factor_ = scale_factor;
  setBaseSize(this->base_size_);
  setBaseMargins(this->base_margins_);
  setBaseFont(this->base_font_);
  setBaseImage(this->base_image_);

  emit scaleFactorChanged(this->scale_factor_);
}

void ScalableMediaEdit::setBaseMargins(const QMargins &margins) {
  this->base_margins_ = margins;
  QLabel::setContentsMargins(margins * this->scale_factor_);

  emit baseMarginsChanged(this->base_margins_);
}

void ScalableMediaEdit::setBaseImage(const QImage &image) {
  this->base_image_ = image;
  if (!base_image_.isNull())
    setPixmap(QPixmap::fromImage(this->base_image_).scaled(
        this->base_size_ * this->scale_factor_, Qt::KeepAspectRatio, Qt::SmoothTransformation));

  emit baseImageChanged(this->base_image_);
}

QSize ScalableMediaEdit::baseSize() { return this->base_size_; }

QFont ScalableMediaEdit::baseFont() { return this->base_font_; }

qreal ScalableMediaEdit::scaleFactor() { return this->scale_factor_; }

QMargins ScalableMediaEdit::baseMargins() { return this->base_margins_; }

QImage ScalableMediaEdit::baseImage() { return this->base_image_; }

