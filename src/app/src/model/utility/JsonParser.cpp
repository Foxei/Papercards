#include "JsonParser.h"

QFont JsonParser::toFont(const QJsonObject &json_node) {
  QFont font;
  if(!json_node.contains("family")){
    qFatal("Parsing field from json node has failed. Missing field: \"family\"");
  }
  if(!json_node["family"].isString()){
    qFatal("Parsing field from json node has failed. Node is not a string: \"family\"");
  }
  QString family = json_node["family"].toString();
  font.setFamily(family);

  if(!json_node.contains("size")){
    qFatal("Parsing field from json node has failed. Missing field: \"size\"");
  }
  if(!json_node["size"].isDouble()){
    qFatal("Parsing field from json node has failed. Node is not a number: \"size\"");
  }
  int size = json_node["size"].toInt();
  font.setPointSize(size);

  return font;
}