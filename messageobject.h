#pragma once

#include "object.h"

#include <QByteArray>
#include <QDateTime>
#include <QString>

class MessageObject final : public Object
{
public:
  MessageObject(const QString& user, const QString& text, const QString& channel, const QDateTime& dateTime);

  void accept(ObjectVisitor&) const override;

  auto getUser() const -> QString;

  auto getText() const -> QString;

  auto getChannel() const -> QString;

  auto getDateTime() const -> QDateTime override;

  auto toJson() const -> QByteArray override;

private:
  QString m_user;

  QString m_text;

  QString m_channel;

  QDateTime m_dateTime;
};
