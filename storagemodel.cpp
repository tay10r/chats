#include "storagemodel.h"

#include <QDirIterator>
#include <QFileInfo>

#include <QDebug>

#include "objectparser.h"

void
StorageModel::initialize(const QString& workspacePath)
{
  QDirIterator dirIterator(workspacePath, QStringList(), QDir::Dirs);

  QMap<QDate, QString> updateQueue;

  while (dirIterator.hasNext()) {

    const QString path = dirIterator.next();

    const QFileInfo dirInfo(path);

    const QDate date = QDate::fromString(dirInfo.baseName(), Qt::ISODate);

    if (date.isValid())
      updateQueue.insert(date, path);
  }

  for (const auto& date : updateQueue.keys())
    updateDate(date, updateQueue[date]);
}

void
StorageModel::updateDate(const QDate& date, const QString& path)
{
  auto existingIt = m_dateMap.find(date);
  if (existingIt != m_dateMap.end())
    m_dateMap.erase(existingIt);

  QDirIterator dirIterator(path, QStringList() << "*.json", QDir::Files);

  ObjectList objects;

  while (dirIterator.hasNext()) {

    const QString objectPath = dirIterator.next();

    ObjectParser objectParser;

    if (auto object = objectParser.parse(objectPath))
      objects.emplace(std::move(object));
  }

  m_dateMap.emplace(date, std::move(objects));
}
