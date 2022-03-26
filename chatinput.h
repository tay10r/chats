#pragma once

#include <QFrame>

#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

class ChatInput final : public QTextEdit
{
  Q_OBJECT
public:
  explicit ChatInput(QWidget* parent);

signals:
  void publish(const QString& message);

private:
  auto getText() const -> QString;

  void keyPressEvent(QKeyEvent* event) override;
};
