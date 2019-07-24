/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file StatusBar.cpp
 */

#include "StatusBar.h"

#include <QSlider>
#include <QLabel>
#include <QDebug>

void StatusBar::setupGui() {
  m_scale_factor_slider = new QSlider(Qt::Horizontal, this);
  m_scale_factor_slider->setMinimum(0);
  m_scale_factor_slider->setMaximum(15);
  m_scale_factor_slider->setSingleStep(1);
  m_scale_factor_slider->setFixedWidth(150);
  m_scale_factor_slider->setTickPosition(QSlider::TicksBothSides);

  auto* minimum_label = new QLabel(this);
  minimum_label->setText(QString("50%"));
  auto* maximum_label = new QLabel(this);
  maximum_label->setText(QString("200%"));

  addPermanentWidget(minimum_label);
  addPermanentWidget(m_scale_factor_slider);
  addPermanentWidget(maximum_label);
}

void StatusBar::setupConnections() {
  connect(m_scale_factor_slider, &QSlider::valueChanged, this, &StatusBar::handleSliderValueChanged);
}

void StatusBar::handleSliderValueChanged(int value) {
  qreal new_scale_factor = ((value+5.0)/10.0);
  m_scale_factor = new_scale_factor;
  emit scaleFactorChanged(new_scale_factor);
}

StatusBar::StatusBar(QWidget *parent) : QStatusBar(parent) {
  setupGui();
  setupConnections();
}

void StatusBar::setScaleFactor(qreal scale_factor) {
  m_scale_factor = scale_factor;
  int new_slider_value = static_cast<int>(m_scale_factor*10.0-5.0);
  m_scale_factor_slider->setValue(new_slider_value);
  showMessage(QString("Zoom to: ")+QString::number(scale_factor*100.0),5000);
}

qreal StatusBar::scaleFactor() const {
  return m_scale_factor;
}
