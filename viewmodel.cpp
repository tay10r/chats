#include "viewmodel.h"

#include "channelobjects.h"
#include "messageobject.h"
#include "object.h"
#include "storagemodel.h"

#include <QObject>

namespace {

class ViewModelBuilder final : public ObjectVisitor
{
public:
  ViewModelBuilder() { m_channels.emplace(QObject::tr("settings"), ViewModel::Channel{}); }

  void visit(const MessageObject& messageObject) override
  {
    auto* channel = findChannel(messageObject.getChannel());

    if (channel)
      channel->messages.emplace(messageObject.getDateTime(), createMessage(messageObject));
  }

  void visit(const ChannelAdditionObject& object) override
  {
    m_channels.emplace(object.getChannelName(), ViewModel::Channel{});
  }

  void visit(const ChannelDeletionObject& object) override
  {
    auto it = m_channels.find(object.getChannelName());
    if (it != m_channels.end())
      m_channels.erase(it);
  }

  auto complete() -> std::map<QString, ViewModel::Channel> { return std::move(m_channels); }

private:
  auto createMessage(const MessageObject& messageObject) -> ViewModel::Message
  {
    return ViewModel::Message{ messageObject.getUser(), messageObject.getText() };
  }

  auto findChannel(const QString& name) -> ViewModel::Channel*
  {
    auto it = m_channels.find(name);
    if (it == m_channels.end())
      return nullptr;
    else
      return &it->second;
  }

private:
  std::map<QString, ViewModel::Channel> m_channels;
};

} // namespace

ViewModel::ViewModel()
{
  m_channels.emplace(QObject::tr("settings"), Channel{});
}

ViewModel::ViewModel(const StorageModel& storageModel)
{
  ViewModelBuilder builder;

  const auto& dateMap = storageModel.getDateMap();

  for (const auto& entry : dateMap) {

    const auto& date = entry.first;

    const auto& objectlist = entry.second;

    for (const auto& object : objectlist)
      object->accept(builder);
  }

  m_channels = builder.complete();
}

auto
ViewModel::findChannel(const QString& name) const -> const Channel*
{
  auto it = m_channels.find(name);
  if (it == m_channels.end())
    return nullptr;
  else
    return &it->second;
}
