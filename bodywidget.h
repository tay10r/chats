#pragma once

#include <QHBoxLayout>
#include <QWidget>

#include "chatwidget.h"
#include "leftwidget.h"

class BodyWidget final : public QWidget
{
  Q_OBJECT
public:
  BodyWidget(QWidget* parent);

  auto getLeftWidget() -> LeftWidget* { return &m_leftWidget; }

  auto getChatWidget() -> ChatWidget* { return &m_chatWidget; }

private:
  QHBoxLayout m_layout{ this };

  LeftWidget m_leftWidget{ this };

  ChatWidget m_chatWidget{ this };
};
