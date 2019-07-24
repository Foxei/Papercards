#include <utility>

/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.cpp
 */
#include "CardEditorBackground.h"

#include <QPainter>
#include <QStyleOption>
#include <QFont>
#include <QDebug>
#include <QString>

void CardEditorBackground::paintEvent(QPaintEvent *event) {
  QStyleOption style;
  style.init(this);
  QFont style_font = font();

  QPainter painter(this);
  painter.setPen(style.palette.base().color());

  for(const DisplayedText& displayed_text : m_displayed_texts){
    style_font.setPointSize(displayed_text.font_size);
    painter.setFont(style_font);
    QPoint position = displayed_text.position;
    QString text = displayed_text.text;
    Qt::Alignment align = displayed_text.align;

    if(align == Qt::AlignRight){
      int width = painter.fontMetrics().width(text);
      position.setX(position.x()-width);
    }

    painter.drawText(position.x(),position.y(),text);
    qInfo() << QString::fromStdString("Paint text:") << text << QString::fromStdString("to:") << position;
  }


  QWidget::paintEvent(event);
}

CardEditorBackground::CardEditorBackground(QWidget *parent,
                                           Qt::WindowFlags flags) : QWidget(
    parent,
    flags) {
  setObjectName(QString("card_editor_background"));
}

void CardEditorBackground::addText(QPoint position,
                                   QString text,
                                   int font_size,
                                   Qt::Alignment align) {
  DisplayedText displayed_text;
  displayed_text.position = position;
  displayed_text.text = std::move(text);
  displayed_text.font_size = font_size;
  displayed_text.align = align;

  m_displayed_texts.append(displayed_text);
}

void CardEditorBackground::moveText(QString text, QPoint position) {
  qInfo() << QString::fromStdString("Try to move text:") << text << QString::fromStdString("to:") << position;

  for(DisplayedText& displayed_text : m_displayed_texts){
    if(displayed_text.text == text){
      displayed_text.position = position;
      qInfo() << QString::fromStdString("Moved text:") << text << QString::fromStdString("to:") << position;
    }
  }
}

void CardEditorBackground::editText(QString old_text, QString new_text) {
  /*for(DisplayedText displayed_text : m_displayed_texts){
    if(displayed_text.text == old_text){
      displayed_text.text = new_text;
    }
  }*/
}

void CardEditorBackground::removeText(QString text) {
  /*for(const DisplayedText& displayed_text : m_displayed_texts){
    if(displayed_text.text == text){
      m_displayed_texts.removeOne(displayed_text);
    }
  }*/
}
