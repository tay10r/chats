#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget* parent)
  : QFrame(parent)
{
  m_layout.addWidget(&m_topWidget);
  m_layout.addWidget(&m_bodyWidget);
  setContentsMargins(0, 0, 0, 0);
}
