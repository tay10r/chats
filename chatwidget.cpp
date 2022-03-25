#include "chatwidget.h"

ChatWidget::ChatWidget(QWidget* parent)
  : QFrame(parent)
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  m_layout.addWidget(&m_chatView);
  m_layout.addWidget(&m_chatInput);
}
