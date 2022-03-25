#pragma once

#include <QWidget>

#include <QLabel>
#include <QVBoxLayout>

class LeftWidget final : public QWidget
{
  Q_OBJECT
public:
  LeftWidget(QWidget* parent);

  QLabel* getWorkspaceTitle() { return &m_title; }

private:
  QVBoxLayout m_layout{ this };

  QLabel m_title{ tr("Example"), this };
};
