#pragma once

#include <QFrame>

#include <QVBoxLayout>

#include "chatinput.h"
#include "chatview.h"

class ChatWidget final : public QFrame
{
  Q_OBJECT
public:
  explicit ChatWidget(QWidget* parent);

  auto getChatView() -> ChatView* { return &m_chatView; }

  auto getChatInput() -> ChatInput* { return &m_chatInput; }

private:
  QVBoxLayout m_layout{ this };

  ChatView m_chatView{ this };

  ChatInput m_chatInput{ this };
};
