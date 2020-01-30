#include "JsonParser.h"

#include <QBuffer>

QFont JsonParser::toFont(const QJsonObject &json_node) {
  QFont font;
  if (!json_node.contains("family")) {
    qFatal("Parsing field from json node has failed. Missing field: \"family\"");
  }
  if (!json_node["family"].isString()) {
    qFatal("Parsing field from json node has failed. Node is not a string: \"family\"");
  }
  QString family = json_node["family"].toString();
  font.setFamily(family);

  if (!json_node.contains("size")) {
    qFatal("Parsing field from json node has failed. Missing field: \"size\"");
  }
  if (!json_node["size"].isDouble()) {
    qFatal("Parsing field from json node has failed. Node is not a number: \"size\"");
  }
  int size = json_node["size"].toInt();
  font.setPointSize(size);

  return font;
}

QJsonObject JsonParser::fontToJson(const QFont &font) {
  QJsonObject object;
  object.insert("family", font.family());
  object.insert("size", font.pointSize());
  return object;
}

QJsonValue JsonParser::imageToJson(const QImage &image) {
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  image.save(&buffer, "PNG");
  auto const encoded = buffer.data().toBase64();
  return {QLatin1String(encoded)};
}

QImage JsonParser::toImage(const QJsonValue &json_node) {
  auto const encoded = json_node.toString().toLatin1();
  QImage p;
  p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
  return p;
}

