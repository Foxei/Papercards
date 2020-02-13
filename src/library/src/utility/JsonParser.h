#ifndef PAPER_CARDS_JSON_PARSER_H
#define PAPER_CARDS_JSON_PARSER_H

#include <QObject>
#include <QJsonObject>
#include <QFont>
#include <QImage>

class JsonParser : public QObject {
 Q_OBJECT

 public:
  static QFont toFont(const QJsonObject &json_node);
  static QJsonObject fontToJson(const QFont &font);

  static QJsonValue imageToJson(const QImage &image);
  static QImage toImage(const QJsonValue &json_node);
};

#endif //PAPER_CARDS_JSON_PARSER_H
