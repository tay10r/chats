#include "message.h"

#include <QJsonDocument>
#include <QJsonObject>

Message::Message(const QString& user, const QString& text)
  : m_user(user)
  , m_text(text)
  , m_time(QTime::currentTime())
{}

auto
Message::getUser() const -> QString
{
  return m_user;
}

auto
Message::getText() const -> QString
{
  return m_text;
}

auto
Message::getTime() const -> QTime
{
  return m_time;
}

auto
Message::toJson() const -> QByteArray
{
  QJsonObject object;
  object["type"] = "message";
  object["text"] = m_text;
  object["time"] = m_time.toString();
  object["user"] = m_user;

  QJsonDocument doc;
  doc.setObject(object);
  return doc.toJson();
}
