#include "chatinput.h"

#include "message.h"

#include <QKeyEvent>

ChatInput::ChatInput(QWidget* parent)
  : QTextEdit(parent)
{
  setPlaceholderText(tr("Send a message here."));

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void
ChatInput::setUser(const QString& user)
{
  m_user = user;
}

void
ChatInput::keyPressEvent(QKeyEvent* event)
{
  if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
    emit publish(Message(m_user, toPlainText()));
  } else {
    QTextEdit::keyPressEvent(event);
  }
}
