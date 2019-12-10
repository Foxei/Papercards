#ifndef SCALABLE_LINE_EDIT_H
#define SCALABLE_LINE_EDIT_H

#include <QLineEdit>

class ScalableLineEdit : public QLineEdit {
 Q_OBJECT
  Q_PROPERTY(QFont base_font
                 READ
                     baseFont
                 WRITE
                     setBaseFont
                 NOTIFY
                 baseFontChanged)

 private:
  qreal scale_factor_ = 1.0;
  QFont base_font_;
  QMargins base_text_margin_;
  QMargins base_margin_;
  qreal base_height_;

 public slots:
  void scale(qreal scale_factor);

 public:
  explicit ScalableLineEdit(QWidget *parent = nullptr);

  void setBaseFont(const QFont &font);

  void setTextMargins(int left, int top, int right, int bottom);
  void setTextMargins(const QMargins &margins);

  void setContentsMargins(int left, int top, int right, int bottom);
  void setContentsMargins(const QMargins &margins);

  QFont baseFont();

 signals:

  void baseFontChanged(QFont);
};

#endif //SCALABLE_LINE_EDIT_H
