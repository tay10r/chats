#include "messageobject.h"

#include <QJsonDocument>
#include <QJsonObject>

MessageObject::MessageObject(const QString& user,
                             const QString& text,
                             const QString& channel,
                             const QDateTime& dateTime)
  : m_user(user)
  , m_text(text)
  , m_channel(channel)
  , m_dateTime(dateTime)
{}

void
MessageObject::accept(ObjectVisitor& visitor) const
{
  visitor.visit(*this);
}

auto
MessageObject::getChannel() const -> QString
{
  return m_channel;
}

auto
MessageObject::getUser() const -> QString
{
  return m_user;
}

auto
MessageObject::getText() const -> QString
{
  return m_text;
}

auto
MessageObject::getDateTime() const -> QDateTime
{
  return m_dateTime;
}

auto
MessageObject::toJson() const -> QByteArray
{
  QJsonObject object;
  object["type"] = "message";
  object["text"] = m_text;
  object["time"] = m_dateTime.toString();
  object["user"] = m_user;
  object["channel"] = m_channel;

  QJsonDocument doc;
  doc.setObject(object);
  return doc.toJson();
}
