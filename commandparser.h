#pragma once

#include <memory>
#include <string>
#include <vector>

#include "commandlexer.h"
#include "commands.h"

template<typename Char>
class CommandParser final
{
public:
  using StringType = std::basic_string<Char>;

  using SizeType = typename StringType::size_type;

  using CommandType = Command<Char>;

  CommandParser(StringType&& data)
    : m_tokens(createTokens(std::move(data)))
  {}

  auto parse() -> std::unique_ptr<CommandType>;

private:
  auto parseChannelAdd() -> std::unique_ptr<CommandType>;

  auto parseChannelDelete() -> std::unique_ptr<CommandType>;

  auto remaining() const -> SizeType
  {
    if (m_offset < m_tokens.size())
      return m_tokens.size() - m_offset;
    else
      return 0;
  }

  void next() { m_offset++; }

  auto peek(SizeType index) const -> const StringType&
  {
    if (index < m_tokens.size())
      return m_tokens[index];
    else
      return m_nullToken;
  }

  static auto createTokens(StringType&& data) -> std::vector<StringType>
  {
    CommandLexer<Char> lexer(std::move(data));
    return lexer.scanAll();
  }

  static bool isEq(const StringType& str, SizeType offset, Char c)
  {
    return (offset < str.size()) ? (str[offset] == c) : false;
  }

private:
  StringType m_nullToken;

  std::vector<StringType> m_tokens;

  SizeType m_offset = 0;
};

template<typename Char>
auto
CommandParser<Char>::parse() -> std::unique_ptr<CommandType>
{
  if (auto command = parseChannelAdd())
    return command;

  if (auto command = parseChannelDelete())
    return command;

  return nullptr;
}

template<typename Char>
auto
CommandParser<Char>::parseChannelAdd() -> std::unique_ptr<CommandType>
{
  if (remaining() != 3)
    return nullptr;

  const auto& add = peek(0);

  // clang-format off
  if (!isEq(add, 0, 'a')
   || !isEq(add, 1, 'd')
   || !isEq(add, 2, 'd')
   || (add.size() != 3))
    return nullptr;
  // clang-format on

  const auto& channel = peek(1);

  // clang-format off
  if (!isEq(channel, 0, 'c')
   || !isEq(channel, 1, 'h')
   || !isEq(channel, 2, 'a')
   || !isEq(channel, 3, 'n')
   || !isEq(channel, 4, 'n')
   || !isEq(channel, 5, 'e')
   || !isEq(channel, 6, 'l')
   || (channel.size() != 7))
    return nullptr;
  // clang-format on

  std::unique_ptr<CommandType> command(new ChannelAdditionCommand<Char>(StringType(peek(2))));

  next();
  next();
  next();

  return command;
}

template<typename Char>
auto
CommandParser<Char>::parseChannelDelete() -> std::unique_ptr<CommandType>
{
  if (remaining() != 3)
    return nullptr;

  const auto& remove = peek(0);

  // clang-format off
  if (!isEq(remove, 0, 'r')
   || !isEq(remove, 1, 'e')
   || !isEq(remove, 2, 'm')
   || !isEq(remove, 3, 'o')
   || !isEq(remove, 4, 'v')
   || !isEq(remove, 5, 'e')
   || (remove.size() != 6))
    return nullptr;
  // clang-format on

  const auto& channel = peek(1);

  // clang-format off
  if (!isEq(channel, 0, 'c')
   || !isEq(channel, 1, 'h')
   || !isEq(channel, 2, 'a')
   || !isEq(channel, 3, 'n')
   || !isEq(channel, 4, 'n')
   || !isEq(channel, 5, 'e')
   || !isEq(channel, 6, 'l')
   || (channel.size() != 7))
    return nullptr;
  // clang-format on

  std::unique_ptr<CommandType> command(new ChannelDeletionCommand<Char>(StringType(peek(2))));

  next();
  next();
  next();

  return command;
}
