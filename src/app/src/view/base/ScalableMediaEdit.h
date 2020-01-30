/**
 * @author Simon Schaefer
 * @date 24. December 2019
 * @file ScalableTextEdit.h
 */

#ifndef SCALABLE_MEDIA_EDIT_H
#define SCALABLE_MEDIA_EDIT_H

#include <QLabel>

/**
 * @brief A QTextEdit that was be modified to scale.
 * @details The scaling will scale the font and the content margins. This doesn't result in a prefect scaling behaviour
 * but the effect should as good as it's needed for the purpose pf an editor.
 */
class ScalableMediaEdit : public QLabel {
  // @formatter:off
  Q_OBJECT
  Q_PROPERTY(QSizeF base_size_ READ baseSize WRITE setBaseSize NOTIFY baseSizeChanged)
  Q_PROPERTY(QFont base_font_ READ baseFont WRITE setBaseFont NOTIFY baseFontChanged)
  Q_PROPERTY(qreal scale_factor_ READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)
  Q_PROPERTY(QMargins base_margins READ baseMargins WRITE setBaseMargins NOTIFY baseMarginsChanged)
  Q_PROPERTY(QImage base_image READ baseImage WRITE setBaseImage NOTIFY baseImageChanged)
  // @formatter:on

 private:
  QSizeF base_size_; ///< Size that is used as a base for scaling.
  QFont base_font_; ///< Font that is used as a base for scaling.
  qreal scale_factor_ = 1.0; ///< Scale factor of the font and margins.
  QMargins base_margins_; ///< Margins that are used as a base for scaling.
  QImage base_image_; ///< Image that are used as a base for scaling.

 public slots:
  /**
   * @brief Setter for the size used as a base for scaling.
   * @details Only the media size is scaled.
   * @see base_size_
   * @param font New base size.
   */
  void setBaseSize(const QSizeF &size);

  /**
   * @brief Setter for the font used as a base for scaling.
   * @details Only the font size is scaled, font weight and other values aren't.
   * @see base_font_
   * @param font New base font.
   */
  void setBaseFont(const QFont &font);

  /**
   * @brief Setter for the scale factor. This will scale the widget.
   * @details This will only scale the font and margins not the size of the widget.
   * @see scale_factor_
   * @param scale_factor New scale factor.
   */
  void setScaleFactor(qreal scale_factor);

  /**
   * @brief Setter for the base margins used for scaling.
   * @details Will not scale the document margins, only the contents margins.
   * @see base_margins_
   * @param margins New base margins.
   */
  void setBaseMargins(const QMargins &margins);

  /**
   * @brief Setter for the base image used for scaling.
   * @see base_image_
   * @param margins New base image.
   */
  void setBaseImage(const QImage &image);

 public:
  /**
   * @brief Will initialise the base font and base margins with the current font and current content margins.
   * @detials Will set the documents margin to 2 so its fit the behaviour of the ScaleAbleLineEdit. Will activate all
   * auto formatting features.
   * @see base_font
   * @see base_margins
   * @see document()
   * @see ScalableLineEdit
   * @param parent
   */
  explicit ScalableMediaEdit(QWidget *parent = nullptr);

  /**
   * @brief Getter for the base size.
   * @see base_size_
   * @return Current base size.
   */
  QSizeF baseSize();

  /**
   * @brief Getter for the base font.
   * @see base_font_
   * @return Current base font.
   */
  QFont baseFont();

  /**
   * @brief Getter for the scale factor.
   * @see scale_factor_
   * @return Current scale factor.
   */
  qreal scaleFactor();

  /**
   * @brief Getter for the base margins.
   * @see base_margins_
   * @return Current base margins.
   */
  QMargins baseMargins();

  /**
   * @brief Getter for the base image.
   * @see base_image_
   * @return Current base image.
   */
  QImage baseImage();

 signals:
  /**
   * @brief Emit of the base size changes.
   * @see base_size_
   */
  void baseSizeChanged(QSizeF);

  /**
 * @brief Emit of the base font changes.
 * @see base_font_
 */
  void baseFontChanged(QFont);

  /**
   * @brief Emit if the scale factor changed.
   * @see scale_factor_
   */
  void scaleFactorChanged(qreal);

  /**
   * @brief Emit if the base margins changed.
   * @see base_margins_
   */
  void baseMarginsChanged(QMargins);

  /**
   * @brief Emit if the base image changed.
   * @see base_image_
   */
  void baseImageChanged(QImage);
};

#endif //SCALABLE_MEDIA_EDIT_H
