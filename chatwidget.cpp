#include "chatwidget.h"

ChatWidget::ChatWidget(const QString& name, QWidget* parent)
  : QFrame(parent)
  , m_name(name)
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  m_layout.addWidget(&m_chatView);
  m_layout.addWidget(&m_chatInput);

  connect(&m_chatInput, &ChatInput::publish, this, &ChatWidget::onChatInputPublish);
}

auto
ChatWidget::getChannelName() const -> QString
{
  return m_name;
}

void
ChatWidget::onChatInputPublish(const QString& text)
{
  emit publish(m_name, text);
}
