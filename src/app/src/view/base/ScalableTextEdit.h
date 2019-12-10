#ifndef SCALABLE_TEXT_EDIT_H
#define SCALABLE_TEXT_EDIT_H

#include <QTextEdit>

class ScalableTextEdit : public QTextEdit {
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
  QMargins base_margin_;

 public slots:
  void scale(qreal scale_factor);

  void setBaseFont(const QFont &font);

 public:
  explicit ScalableTextEdit(QWidget *parent = nullptr);

  void setContentsMargins(int left, int top, int right, int bottom);
  void setContentsMargins(const QMargins &margins);

  QFont baseFont();

 signals:

  void baseFontChanged(QFont);
};

#endif //SCALABLE_TEXT_EDIT_H
