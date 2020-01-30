#ifndef PAPER_CARDS_CARD_VIEW_H
#define PAPER_CARDS_CARD_VIEW_H

#include "view/base/ScalableVBoxLayout.h"
#include "view/base/ScalableLineEdit.h"
#include "view/base/ScalableTextEdit.h"
#include "view/base/ScalableMediaEdit.h"

#include <QFrame>
#include <QPageSize>
#include <QLineEdit>
#include <QTextEdit>
#include <QPageLayout>

class CardView : public QFrame {
  //@formatter:off
  Q_OBJECT
  Q_PROPERTY(qreal scale_factor_ READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)
  //@formatter:on

 private:
  QSizeF base_content_size;

  qreal scale_factor_ = 1.0; ///< Scale factor of the font and margins.

  ScalableVBoxLayout *content_layout_ = nullptr;
  ScalableLineEdit *title_text_edit_ = nullptr;
  ScalableTextEdit *content_text_edit_ = nullptr;
  ScalableMediaEdit *media_edit_ = nullptr;

  bool font_site_;

 private:

  void setupGui();

  void setupConnections();

 public:

  explicit CardView(bool front_site, QWidget *parent = Q_NULLPTR);

  void dragEnterEvent(QDragEnterEvent *event) override;

  void dropEvent(QDropEvent *event) override;

  /**
   * @brief Getter for the scale factor.
   * @see scale_factor_
   * @return Current scale factor.
   */
  qreal scaleFactor();

 private slots:
  void titleEdited();

  void contentEdited();

 public slots:

  /**
   * @brief Setter for the scale factor. This will scale the widget.
   * @details This will only scale the font and margins not the size of the widget.
   * @see scale_factor_
   * @param scale_factor New scale factor.
   */
  void setScaleFactor(qreal scale_factor);

  void updateBaseContentSize();

  void updateCardElement(const QString &field_name, const QVariant &field_content);

  void updateCardElementFont(const QString &field_name, const QFont &field_font);

  void showCardElement(const QString &field_name, bool visible);

 signals:

  /**
   * @brief Emit if the scale factor changed.
   * @see scale_factor_
   */
  void scaleFactorChanged(qreal);

  void cardElementUpdated(const QString &field_name, const QVariant &field_content);

};

#endif //PAPER_CARDS_CARD_VIEW_H
