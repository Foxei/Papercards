#ifndef PAPERCARDS_QML_BACKEND_H
#define PAPERCARDS_QML_BACKEND_H

#include <QObject>
#include <QString>

class BackEnd : public QObject {
  // @formatter::off
 Q_OBJECT
  Q_PROPERTY(QString userName
                 READ
                 userName
                 WRITE
                 setUserName
                 NOTIFY
                 userNameChanged)
  // @formatter::on

 private:
  QString m_userName;

 public:
  explicit BackEnd(QObject *parent = nullptr);

  QString userName();
  void setUserName(const QString &userName);

 signals:
  void userNameChanged();

};

#endif //PAPERCARDS_QML_BACKEND_H
