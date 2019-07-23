/**
 * @author Simon Schaefer
 * @date 18.07.2019
 * @file CardEditor.h
 */
#ifndef PAPERCARDS_CARDEDITORBACKGROUND_H
#define PAPERCARDS_CARDEDITORBACKGROUND_H

#include <QWidget>
#include <QList>

struct DisplayedText {
  QPoint position = {0,0};
  QString text = "";
  int font_size = 10;
  Qt::Alignment align = Qt::AlignLeft;
};

class CardEditorBackground : public QWidget{
 private:
  QList<DisplayedText> m_displayed_texts;

 protected:
  void paintEvent(QPaintEvent *event) override;

 public:
  explicit CardEditorBackground(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

  void addText(QPoint position, QString text, int font_size, Qt::Alignment align);
  void moveText(QString text, QPoint position);
  void editText(QString old_text, QString new_text);
  void removeText(QString text);
};

#endif //PAPERCARDS_CARDEDITORBACKGROUND_H
