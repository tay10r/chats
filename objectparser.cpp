#include "objectparser.h"

#include "channelobjects.h"
#include "messageobject.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

auto
ObjectParser::parse(const QString& path) -> std::unique_ptr<Object>
{
  QFile file(path);

  if (!file.open(QFile::ReadOnly))
    return nullptr;

  auto doc = QJsonDocument::fromJson(file.readAll());

  if (!doc.isObject())
    return nullptr;

  auto obj = doc.object();

  auto type = obj["type"].toString();
  if (type.isEmpty())
    return nullptr;

  if (type == "message")
    return parseMessage(obj);
  else if (type == "channel-addition")
    return parseChannelAddition(obj);
  else if (type == "channel-deletion")
    return parseChannelDeletion(obj);

  return nullptr;
}

auto
ObjectParser::parseChannelAddition(const QJsonObject& obj) -> std::unique_ptr<Object>
{
  auto user = obj["user"].toString();
  auto channel = obj["channel"].toString();
  auto dateTime = QDateTime::fromString(obj["time"].toString());
  return std::unique_ptr<Object>(new ChannelAdditionObject(channel, user, dateTime));
}

auto
ObjectParser::parseChannelDeletion(const QJsonObject& obj) -> std::unique_ptr<Object>
{
  auto user = obj["user"].toString();
  auto channel = obj["channel"].toString();
  auto dateTime = QDateTime::fromString(obj["time"].toString());
  return std::unique_ptr<Object>(new ChannelDeletionObject(channel, user, dateTime));
}

auto
ObjectParser::parseMessage(const QJsonObject& obj) -> std::unique_ptr<Object>
{
  auto user = obj["user"].toString();
  auto text = obj["text"].toString();
  auto channel = obj["channel"].toString();
  auto dateTime = QDateTime::fromString(obj["time"].toString());
  return std::unique_ptr<Object>(new MessageObject(user, text, channel, dateTime));
}
