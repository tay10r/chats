#pragma once

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QTime>

class Message final : public QObject
{
  Q_OBJECT
public:
  explicit Message(const QString& user, const QString& text);

  auto getUser() const -> QString;

  auto getText() const -> QString;

  auto getTime() const -> QTime;

  auto toJson() const -> QByteArray;

private:
  QString m_user;

  QString m_text;

  QTime m_time;
};
