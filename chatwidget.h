#pragma once

#include <QFrame>

#include <QString>
#include <QVBoxLayout>

#include "chatinput.h"
#include "chatview.h"

class ChatWidget final : public QFrame
{
  Q_OBJECT
public:
  explicit ChatWidget(const QString& name, QWidget* parent);

  auto getChannelName() const -> QString;

  auto getChatView() -> ChatView* { return &m_chatView; }

  auto getChatInput() -> ChatInput* { return &m_chatInput; }

signals:
  void publish(const QString& channelName, const QString& text);

private:
  void onChatInputPublish(const QString& text);

private:
  QString m_name;

  QVBoxLayout m_layout{ this };

  ChatView m_chatView{ this };

  ChatInput m_chatInput{ this };
};
