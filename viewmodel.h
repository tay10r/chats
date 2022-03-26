#pragma once

#include <QDateTime>
#include <QString>

#include <map>

class StorageModel;

class ViewModel final
{
public:
  struct Message final
  {
    QString user;

    QString text;
  };

  struct Channel final
  {
    std::map<QDateTime, Message> messages;
  };

  using ChannelMap = std::map<QString, Channel>;

  ViewModel();

  ViewModel(const StorageModel&);

  auto findChannel(const QString& name) const -> const Channel*;

  auto getChannelMap() const -> const ChannelMap& { return m_channels; }

private:
  ChannelMap m_channels;
};
