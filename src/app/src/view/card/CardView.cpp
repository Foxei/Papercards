#include "CardView.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QDropEvent>
#include <QMimeData>
#include <QFile>
#include <QImage>
#include <QImageReader>

void CardView::setScaleFactor(qreal scale_factor) {
  this->scale_factor_ = scale_factor;
  emit scaleFactorChanged(this->scale_factor_);
}

void CardView::showCard(Card *card) {
  const double CORRECTION_FACTOR = 0.95;

  qInfo("Received signal to show card in editor.");
  if (!card) return;
  this->current_card = card;
  this->base_content_size = content_text_edit_->size() / this->scale_factor_;

  Field *title_field = card->getField("title", this->site_);
  if (title_field) {
    this->title_text_edit_->setBaseFont(title_field->font());
    this->title_text_edit_->setText(title_field->text());
  }

  Field *content_field = card->getField("content", this->site_);
  if (content_field) {
    this->content_text_edit_->setBaseFont(content_field->font());
    this->content_text_edit_->setText(content_field->text());
  }

  Field *media_field = card->getField("media", this->site_);
  if (media_field) {
    this->media_edit_->setBaseFont(media_field->font());
    this->media_edit_->setText(media_field->text());
    this->media_edit_->setBaseSize(base_content_size * CORRECTION_FACTOR);
    this->media_edit_->setBaseImage(media_field->image());
  }

  switch (card->getStyle(this->site_)) {
    case Card::Style::TITLE_ONLY :this->title_text_edit_->setVisible(true);
      this->content_text_edit_->setVisible(false);
      this->media_edit_->setVisible(false);
      break;
    case Card::Style::TITLE_CONTENT :this->title_text_edit_->setVisible(true);
      this->content_text_edit_->setVisible(true);
      this->media_edit_->setVisible(false);
      break;
    case Card::Style::TITLE_MEDIA :this->title_text_edit_->setVisible(true);
      this->content_text_edit_->setVisible(false);
      this->media_edit_->setVisible(true);
      break;
  }
  this->title_text_edit_->setFocus();
}

void CardView::setupGui() {
  content_layout_ = new ScalableVBoxLayout(this);

  title_text_edit_ = new ScalableLineEdit(this);
  title_text_edit_->setObjectName("card-title");
  content_text_edit_ = new ScalableTextEdit(this);
  content_text_edit_->setObjectName("card-content");
  media_edit_ = new ScalableMediaEdit(this);
  media_edit_->setObjectName("card-media");
  media_edit_->setAlignment(Qt::AlignCenter);
  media_edit_->setVisible(false);

  content_layout_->addWidget(title_text_edit_);
  content_layout_->addWidget(content_text_edit_);
  content_layout_->addWidget(media_edit_);
  content_layout_->setStretch(0, 5);
  content_layout_->setStretch(1, 5);
  content_layout_->setStretch(2, 5);
  content_layout_->setAlignment(Qt::AlignCenter);

  this->setLayout(content_layout_);
  this->setAcceptDrops(true);
}

void CardView::setupConnections() {
  connect(this, &CardView::scaleFactorChanged, this->media_edit_, &ScalableMediaEdit::setScaleFactor);
  connect(this, &CardView::scaleFactorChanged, this->title_text_edit_, &ScalableLineEdit::scale);
  connect(this, &CardView::scaleFactorChanged, this->content_text_edit_, &ScalableTextEdit::setScaleFactor);
  connect(this, &CardView::scaleFactorChanged, this->content_layout_, &ScalableVBoxLayout::scale);
}

CardView::CardView(Card::Site site, QWidget *parent) : QFrame(parent) {
  this->site_ = site;
  setupGui();
  setupConnections();
}

void CardView::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasFormat("text/uri-list"))
    event->acceptProposedAction();
}

void CardView::dropEvent(QDropEvent *event) {
  const double CORRECTION_FACTOR = 0.95;
  if (!event->mimeData()->hasFormat("text/uri-list")) {
    event->ignore();
    return;
  }
  QString uri_list_string = event->mimeData()->text();
  QStringList uri_list = uri_list_string.split("\n");
  QUrl uri(uri_list.front());
  QString uri_string = uri.toString(QUrl::RemoveScheme);
  QImageReader reader(uri_string);
  QImage image = reader.read();

  QSize size_shift(
      -contentsMargins().right() - contentsMargins().left(),
      -contentsMargins().top() - contentsMargins().bottom());

  QSize destination_size((this->base_content_size - size_shift) * CORRECTION_FACTOR);

  QSize source_size = image.size();

  qreal image_scale = std::min(
      1.0 * destination_size.width() / source_size.width(),
      1.0 * destination_size.height() / source_size.height());

  media_edit_->setBaseSize(source_size * image_scale);
  media_edit_->setBaseImage(image);

  if (current_card) {
    Field *media_field = current_card->getField("media", this->site_);
    if (media_field) {
      media_field->setImage(image);
      qInfo("Media of card updated!");
    }
  }

  event->acceptProposedAction();
}

qreal CardView::scaleFactor() {
  return scale_factor_;
}
