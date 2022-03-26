#pragma once

#include <string>

template<typename Char>
class ChannelAdditionCommand;

template<typename Char>
class ChannelDeletionCommand;

template<typename Char>
class CommandVisitor
{
public:
  virtual ~CommandVisitor() = default;

  virtual void visit(const ChannelAdditionCommand<Char>&) = 0;

  virtual void visit(const ChannelDeletionCommand<Char>&) = 0;
};

template<typename Char>
class Command
{
public:
  virtual ~Command() = default;

  virtual void accept(CommandVisitor<Char>&) const = 0;
};

template<typename Char>
class ChannelAdditionCommand final : public Command<Char>
{
public:
  using StringType = std::basic_string<Char>;

  ChannelAdditionCommand(StringType&& channelName)
    : m_channelName(channelName)
  {}

  void accept(CommandVisitor<Char>& visitor) const override { visitor.visit(*this); }

  auto getChannelName() const -> const StringType& { return m_channelName; }

private:
  StringType m_channelName;
};

template<typename Char>
class ChannelDeletionCommand final : public Command<Char>
{
public:
  using StringType = std::basic_string<Char>;

  ChannelDeletionCommand(StringType&& channelName)
    : m_channelName(channelName)
  {}

  void accept(CommandVisitor<Char>& visitor) const override { visitor.visit(*this); }

  auto getChannelName() const -> const StringType& { return m_channelName; }

private:
  StringType m_channelName;
};
