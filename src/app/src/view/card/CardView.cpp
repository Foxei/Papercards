#include "CardView.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QApplication>

void CardView::scaleCards(qreal scale_factor) {
  this->scale_factor_ = scale_factor;
  this->content_layout_->scale(scale_factor_);
  this->title_text_edit_->scale(scale_factor_);
  this->content_text_edit_->setScaleFactor(scale_factor_);
}

void CardView::showCard(Card* card){
  qInfo("Received signal to show card in editor.");
  if(!card) return;

  Field* title_field = card->getField("title", this->site_);
  if(title_field){
    this->title_text_edit_->setVisible(true);
    this->title_text_edit_->setBaseFont(title_field->font());
    this->title_text_edit_->setText(title_field->text());
  }
  else this->title_text_edit_->setVisible(false);

  Field* content_field = card->getField("content", this->site_);
  if(content_field){
    this->content_text_edit_->setVisible(true);
    this->content_text_edit_->setBaseFont(content_field->font());
    this->content_text_edit_->setText(content_field->text());
  }
  else this->content_text_edit_->setVisible(false);

  this->title_text_edit_->setFocus();
}


void CardView::setupGui() {
  content_layout_ = new ScalableVBoxLayout(this);

  title_text_edit_ = new ScalableLineEdit(this);
  title_text_edit_->setObjectName("card-title");
  content_text_edit_ = new ScalableTextEdit(this);
  content_text_edit_->setObjectName("card-content");

  content_layout_->addWidget(title_text_edit_);
  content_layout_->addWidget(content_text_edit_);
  content_layout_->setStretch(0, 5);
  content_layout_->setStretch(1, 5);

  this->setLayout(content_layout_);
}

void CardView::setupConnections() {
}

CardView::CardView(Card::Site site, QWidget *parent) : QFrame(parent) {
  this->site_ = site;
  setupGui();
  setupConnections();
}