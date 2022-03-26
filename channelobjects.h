#pragma once

#include "object.h"

#include <QDateTime>
#include <QString>

template<typename Derived>
class ChannelModifierObject : public Object
{
public:
  ChannelModifierObject(const QString& name, const QString& user, const QDateTime& dateTime)
    : m_name(name)
    , m_user(user)
    , m_dateTime(dateTime)
  {}

  void accept(ObjectVisitor& visitor) const override { return visitor.visit(static_cast<const Derived&>(*this)); }

  auto getChannelName() const -> QString { return m_name; }

  auto getDateTime() const -> QDateTime override { return m_dateTime; }

  auto getUser() const -> QString { return m_user; }

private:
  QString m_name;

  QString m_user;

  QDateTime m_dateTime;
};

class ChannelAdditionObject final : public ChannelModifierObject<ChannelAdditionObject>
{
public:
  using ChannelModifierObject<ChannelAdditionObject>::ChannelModifierObject;

  auto toJson() const -> QByteArray override;
};

class ChannelDeletionObject final : public ChannelModifierObject<ChannelDeletionObject>
{
public:
  using ChannelModifierObject<ChannelDeletionObject>::ChannelModifierObject;

  auto toJson() const -> QByteArray override;
};
