#pragma once

#include <QScrollArea>

#include <QVBoxLayout>

class ChatView final : public QScrollArea
{
  Q_OBJECT
public:
  explicit ChatView(QWidget* parent);

  void scanDirectory(const QString& path);

private:
  QVBoxLayout m_layout{ this };
};
