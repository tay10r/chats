#pragma once

#include <memory>

#include "object.h"

class QJsonObject;
class QString;

class ObjectParser final
{
public:
  auto parse(const QString& path) -> std::unique_ptr<Object>;

private:
  auto parseChannelAddition(const QJsonObject&) -> std::unique_ptr<Object>;

  auto parseChannelDeletion(const QJsonObject&) -> std::unique_ptr<Object>;

  auto parseMessage(const QJsonObject&) -> std::unique_ptr<Object>;
};
