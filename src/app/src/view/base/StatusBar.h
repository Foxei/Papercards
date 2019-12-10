/**
 * @author Simon Schaefer
 * @date 24.07.2019
 * @file StatusBar.h
 */
#ifndef PAPER_CARDS_STATUS_BAR_H
#define PAPER_CARDS_STATUS_BAR_H

#include <QStatusBar>
#include <QSlider>

class StatusBar : public QStatusBar {
  Q_OBJECT
  Q_PROPERTY(qreal scale_factor READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)

 private:
  QSlider* m_scale_factor_slider = Q_NULLPTR;
  qreal m_scale_factor = 1.0;

  void setupGui();

  void setupConnections();

 private slots:

  void handleSliderValueChanged(int value);

 public:

  explicit StatusBar(QWidget *parent = Q_NULLPTR);

  qreal scaleFactor() const;

 public slots:
  void setScaleFactor(qreal scale_factor);

 signals:
  void scaleFactorChanged(qreal scale_factor);
};

#endif //PAPER_CARDS_STATUS_BAR_H
