#ifndef PAPER_CARDS_JSON_PARSER_H
#define PAPER_CARDS_JSON_PARSER_H

#include <QObject>
#include <QJsonObject>
#include <QFont>

class JsonParser : public QObject {
 Q_OBJECT

 public:
  static QFont toFont(const QJsonObject &json_node);
};

#endif //PAPER_CARDS_JSON_PARSER_H
