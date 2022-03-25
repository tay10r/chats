#include "leftwidget.h"

LeftWidget::LeftWidget(QWidget* parent)
  : QWidget(parent)
{
  m_layout.addWidget(&m_title);

  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}
