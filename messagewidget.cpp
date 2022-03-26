#include "messagewidget.h"

#include "messageobject.h"

#include <QTextStream>

MessageWidget::MessageWidget(const ViewModel::Message& message, const QDateTime& dateTime, QWidget* parent)
  : QLabel(parent)
{
  const auto user = message.user;

  const auto safeUser = user.isEmpty() ? QString("(Anonymous)") : user;

  QString data;

  QTextStream stream(&data);

  stream << "<b>" << safeUser << "</b>";

  if (dateTime.date() != QDate::currentDate())
    stream << " @ " << dateTime.toString();
  else
    stream << " @ " << dateTime.time().toString();

  stream << message.text;

  setText(data);

  setOpenExternalLinks(true);
}
