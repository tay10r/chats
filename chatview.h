#pragma once

#include <QScrollArea>

#include <QVBoxLayout>

#include <vector>

#include "viewmodel.h"

class MessageWidget;

class ChatView final : public QScrollArea
{
  Q_OBJECT
public:
  explicit ChatView(QWidget* parent);

  void update(const ViewModel::Channel&);

private:
  void scrollToBottom(int scrollMin, int scrollMax);

private:
  QFrame m_target{ this };

  QVBoxLayout m_layout{ &m_target };

  std::vector<MessageWidget*> m_messageWidgets;
};
