#include "topwidget.h"

TopWidget::TopWidget(QWidget* parent)
  : QFrame(parent)
{
  setObjectName("TopWidget");

  setMinimumSize(96, 96);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}
