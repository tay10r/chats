#pragma once

#include <string>
#include <vector>

template<typename Char>
class CommandLexer final
{
public:
  using StringType = std::basic_string<Char>;

  using SizeType = typename StringType::size_type;

  CommandLexer(StringType&& data)
    : m_data(std::move(data))
  {}

  auto atEnd() const noexcept -> bool { return m_offset >= m_data.size(); }

  auto scanAll() -> std::vector<StringType>;

  auto scan() -> StringType;

private:
  auto scanString(char leadingQuote) -> StringType;

  auto scanWord() -> StringType;

  void skipWhitespace();

  void next()
  {
    if (!atEnd())
      m_offset++;
  }

  auto outOfBounds(SizeType relativeOffset) const -> bool
  {
    const SizeType absOffset = m_offset + relativeOffset;

    return absOffset >= m_data.size();
  }

  auto peek(SizeType relativeOffset) const -> Char
  {
    const SizeType absOffset = m_offset + relativeOffset;

    return (absOffset < m_data.size()) ? m_data[absOffset] : 0;
  }

  static auto isWhitespace(char c) -> bool { return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n'); }

private:
  StringType m_data;

  SizeType m_offset = 0;
};

template<typename Char>
auto
CommandLexer<Char>::scanAll() -> std::vector<StringType>
{
  std::vector<StringType> tokens;

  while (!atEnd()) {
    auto token = scan();

    if (token.empty())
      break;

    tokens.emplace_back(std::move(token));
  }

  return tokens;
}

template<typename Char>
void
CommandLexer<Char>::skipWhitespace()
{
  while (!atEnd()) {
    if (isWhitespace(peek(0)))
      next();
    else
      break;
  }
}

template<typename Char>
auto
CommandLexer<Char>::scan() -> StringType
{
  skipWhitespace();

  const auto leadingChar = peek(0);

  if ((leadingChar == '\'') || (leadingChar == '"'))
    return scanString(leadingChar);
  else
    return scanWord();
}

template<typename Char>
auto
CommandLexer<Char>::scanString(char leadingQuote) -> StringType
{
  next();

  StringType output;

  while (!atEnd()) {
    const auto c = peek(0);
    if (c == leadingQuote) {
      next();
      break;
    } else if (c == '\'') {
      next();
    } else {
      output.push_back(peek(0));
      next();
    }
  }

  return output;
}

template<typename Char>
auto
CommandLexer<Char>::scanWord() -> StringType
{
  StringType output;

  while (!atEnd()) {
    const auto c = peek(0);
    if (isWhitespace(c)) {
      break;
    } else {
      output.push_back(c);
      next();
    }
  }
  return output;
}
