#include "chatinput.h"

#include "messageobject.h"

#include <QKeyEvent>

ChatInput::ChatInput(QWidget* parent)
  : QTextEdit(parent)
{
  setObjectName("ChatInput");

  setPlaceholderText(tr("Send a message here."));

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void
ChatInput::keyPressEvent(QKeyEvent* event)
{
  const bool isEnter = ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return));

  const bool isShift = event->modifiers() & Qt::ShiftModifier;

  if (isEnter && !isShift) {
    emit publish(getText());
  } else {
    QTextEdit::keyPressEvent(event);
  }
}

auto
ChatInput::getText() const -> QString
{
  return toPlainText();
}
