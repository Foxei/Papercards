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
  this->content_text_edit_->scale(scale_factor_);
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

CardView::CardView(QWidget *parent) : QFrame(parent) {
  setupGui();
  setupConnections();
}
