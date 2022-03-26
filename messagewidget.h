#pragma once

#include <QLabel>

#include "object.h"
#include "viewmodel.h"

class MessageObject;

class MessageWidget final : public QLabel
{
public:
  explicit MessageWidget(const ViewModel::Message&, const QDateTime& dateTime, QWidget* parent);
};
