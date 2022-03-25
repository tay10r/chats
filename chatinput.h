#pragma once

#include <QTextEdit>

class Message;

class ChatInput final : public QTextEdit
{
  Q_OBJECT
public:
  explicit ChatInput(QWidget* parent);

  void setUser(const QString& user);

signals:
  void publish(const Message&);

private:
  void keyPressEvent(QKeyEvent* event) override;

private:
  QString m_user;
};
