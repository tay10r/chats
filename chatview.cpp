#include "chatview.h"

#include <QDirIterator>

ChatView::ChatView(QWidget* parent)
  : QScrollArea(parent)
{}

void
ChatView::scanDirectory(const QString& path)
{
  QDirIterator dirIterator(path);

  while (dirIterator.hasNext()) {
    const QString path = dirIterator.next();
  }
}
