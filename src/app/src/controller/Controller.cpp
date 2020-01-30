#include "Controller.h"

#include "view/View.h"
#include "../../../library/src/papercardsmodel/Model.h"

void Controller::init() {

}

void Controller::free() {

}

void Controller::connectModelAndView() {
  Model *model = Model::instance();
  View *view = View::instance();
}

void Controller::showSite(Card::Site site, Card *card) {
  if (card == nullptr)
    qFatal("No card is given to display.");

  bool front = (site == Card::Site::FRONT);

  switch (card->getStyle(site)) {
    case Card::Style::TITLE_MEDIA:emit showCardElement(front, "title", true);
      emit showCardElement(front, "media", true);
      emit showCardElement(front, "content", false);

      emit updateCardElement(front, "title", card->getField("title", site)->text());
      emit updateCardElementFont(front, "title", card->getField("title", site)->font());
      emit updateCardElement(front, "media", card->getField("media", site)->image());
      emit updateCardElementFont(front, "media", card->getField("media", site)->font());
      break;
    case Card::Style::TITLE_CONTENT:emit showCardElement(front, "title", true);
      emit showCardElement(front, "media", false);
      emit showCardElement(front, "content", true);

      emit updateCardElement(front, "title", card->getField("title", site)->text());
      emit updateCardElementFont(front, "title", card->getField("title", site)->font());
      emit updateCardElement(front, "content", card->getField("content", site)->text());
      emit updateCardElementFont(front, "content", card->getField("content", site)->font());
      break;
    case Card::Style::TITLE_ONLY:emit showCardElement(front, "title", true);
      emit showCardElement(front, "media", false);
      emit showCardElement(front, "content", false);

      emit updateCardElement(front, "title", card->getField("title", site)->text());
      emit updateCardElementFont(front, "title", card->getField("title", site)->font());
      break;
    case Card::Style::UNKNOWN:qFatal("Unknown card style.");
  }
}

void Controller::showCard(Card *card) {
  if (card == nullptr)
    qFatal("No card is given to display.");
  this->current_displayed_card = card;
  emit updateCardSize(card->size().size(QPageSize::Inch), card->orientation());

  showSite(Card::Site::FRONT, card);
  showSite(Card::Site::BACK, card);
}

void Controller::updateModelData(bool front, const QString &field_name, const QVariant &field_content) {
  if (current_displayed_card == nullptr)
    qFatal("No card is displayed to update.");

  Field *field = current_displayed_card->getField(field_name, front ? Card::Site::FRONT : Card::Site::BACK);
  if (field == nullptr)
    qFatal("No field with given name found to update.");

  if (!field_content.isValid()) {
    qFatal("No content found to update with.");
  }

  if (field_content.canConvert<QImage>()) {
    field->setImage(field_content.value<QImage>());
  } else {
    field->setText(field_content.value<QString>());
  }
}

