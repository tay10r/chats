#pragma once

#include "object.h"

#include <QDate>

#include <map>
#include <memory>
#include <set>

class StorageModel final
{
public:
  struct ObjectComparator final
  {
    auto operator()(const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b) const -> bool
    {
      return a->getDateTime().time() < b->getDateTime().time();
    }
  };

  using ObjectList = std::set<std::unique_ptr<Object>, ObjectComparator>;

  using DateMap = std::map<QDate, ObjectList>;

  void initialize(const QString& workspacePath);

  void updateDate(const QDate& date, const QString& path);

  auto getDateMap() const -> const DateMap& { return m_dateMap; }

private:
  DateMap m_dateMap;
};
