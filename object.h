#pragma once

class QDateTime;
class QByteArray;

class MessageObject;
class ChannelAdditionObject;
class ChannelDeletionObject;

class ObjectVisitor
{
public:
  virtual ~ObjectVisitor() = default;

  virtual void visit(const MessageObject&) = 0;

  virtual void visit(const ChannelAdditionObject&) = 0;

  virtual void visit(const ChannelDeletionObject&) = 0;
};

class Object
{
public:
  virtual ~Object() = default;

  virtual void accept(ObjectVisitor&) const = 0;

  virtual auto getDateTime() const -> QDateTime = 0;

  virtual auto toJson() const -> QByteArray = 0;
};
