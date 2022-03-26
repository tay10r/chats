#include "chatview.h"

#include <QDirIterator>
#include <QScrollBar>
#include <QTimer>

#include "messagewidget.h"

#include <vector>

ChatView::ChatView(QWidget* parent)
  : QScrollArea(parent)
{
  setObjectName("ChatView");

  setWidget(&m_target);

  setWidgetResizable(true);

  connect(verticalScrollBar(), &QAbstractSlider::rangeChanged, this, &ChatView::scrollToBottom);
}

void
ChatView::update(const ViewModel::Channel& channel)
{
  for (int i = 0; i < m_messageWidgets.size(); i++) {

    m_layout.removeWidget(m_messageWidgets[i]);

    m_messageWidgets[i]->deleteLater();
  }

  m_messageWidgets.clear();

  for (const auto& entry : channel.messages) {

    auto* messageWidget = new MessageWidget(entry.second, entry.first, &m_target);

    m_messageWidgets.emplace_back(messageWidget);

    m_layout.addWidget(messageWidget);
  }
}

void
ChatView::scrollToBottom(int scrollMin, int scrollMax)
{
  verticalScrollBar()->setValue(scrollMax);
}
