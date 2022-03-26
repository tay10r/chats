#include "channelobjects.h"

#include <QJsonDocument>
#include <QJsonObject>

auto
ChannelAdditionObject::toJson() const -> QByteArray
{
  QJsonObject object;
  object["type"] = "channel-addition";
  object["channel"] = getChannelName();
  object["time"] = getDateTime().toString();
  object["user"] = getUser();

  QJsonDocument doc;
  doc.setObject(object);
  return doc.toJson();
}

auto
ChannelDeletionObject::toJson() const -> QByteArray
{
  QJsonObject object;
  object["type"] = "channel-deletion";
  object["channel"] = getChannelName();
  object["time"] = getDateTime().toString();
  object["user"] = getUser();

  QJsonDocument doc;
  doc.setObject(object);
  return doc.toJson();
}
