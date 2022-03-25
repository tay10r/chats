#pragma once

#include <QFrame>

#include <QVBoxLayout>

#include "bodywidget.h"
#include "topwidget.h"

class CentralWidget final : public QFrame
{
  Q_OBJECT
public:
  CentralWidget(QWidget* parent);

  auto getBodyWidget() -> BodyWidget* { return &m_bodyWidget; }

private:
  QVBoxLayout m_layout{ this };

  TopWidget m_topWidget{ this };

  BodyWidget m_bodyWidget{ this };
};
