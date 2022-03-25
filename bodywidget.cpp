#include "bodywidget.h"

BodyWidget::BodyWidget(QWidget* parent)
  : QWidget(parent)
{
  m_layout.addWidget(&m_leftWidget);
  m_layout.addWidget(&m_chatWidget);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
