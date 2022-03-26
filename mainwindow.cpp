#include "mainwindow.h"

#include "chatwidget.h"
#include "commandparser.h"
#include "viewmodel.h"

#include "channelobjects.h"
#include "messageobject.h"

#include <QByteArray>
#include <QCryptographicHash>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(const QString& workspacePath, const QString& userName, QWidget* parent)
  : QMainWindow(parent)
  , m_workspacePath(workspacePath)
  , m_currentPath(createCurrentDirectory(m_workspacePath))
  , m_userName(userName)
  , m_fsWatcher(QStringList(m_currentPath), this)
{
  setCentralWidget(&m_channelTabs);

  addChannelWidget(new ChatWidget(tr("settings"), &m_channelTabs));

  m_storageModel.initialize(workspacePath);

  handleStorageModelUpdate();

  connect(&m_fsWatcher, &QFileSystemWatcher::directoryChanged, this, &MainWindow::onDirectoryChanged);
}

MainWindow::~MainWindow() {}

void
MainWindow::commitObject(const Object& object)
{
  const auto jsonData = object.toJson();

  const auto hash = getHash(jsonData);

  const auto path = m_currentPath + QDir::separator() + hash + ".json";

  const QFileInfo fileInfo(path);

  if (fileInfo.exists()) {
    // TODO : error message (hash collision)
    return;
  }

  QFile file(path);

  if (!file.open(QIODevice::WriteOnly)) {

    // TODO : error message

  } else {

    file.write(jsonData);

    getCurrentChannelWidget()->getChatInput()->clear();
  }
}

void
MainWindow::visit(const ChannelAdditionCommand<char>& command)
{
  const QString channelName(command.getChannelName().c_str());

  commitObject(ChannelAdditionObject(channelName, m_userName, QDateTime::currentDateTime()));
}

void
MainWindow::visit(const ChannelDeletionCommand<char>& command)
{
  const QString channelName(command.getChannelName().c_str());

  commitObject(ChannelDeletionObject(channelName, m_userName, QDateTime::currentDateTime()));
}

void
MainWindow::onPublish(const QString& channel, const QString& text)
{
  if (channel == tr("settings"))
    return onSettingsMessage(text);
  else
    return onStandardMessage(channel, text);
}

void
MainWindow::onSettingsMessage(const QString& text)
{
  CommandParser<char> commandParser(text.toStdString());

  if (auto command = commandParser.parse())
    command->accept(*this);
}

void
MainWindow::onStandardMessage(const QString& channel, const QString& text)
{
  const MessageObject message(m_userName, text, channel, QDateTime::currentDateTime());

  commitObject(message);
}

void
MainWindow::onDirectoryChanged(const QString& path)
{
  const QFileInfo fileInfo(path);

  const QString baseName = fileInfo.baseName();

  const QDate date = QDate::fromString(baseName, Qt::ISODate);

  if (!date.isValid()) {
    // TODO : error
    return;
  }

  m_storageModel.updateDate(date, path);

  handleStorageModelUpdate();
}

void
MainWindow::addChannelWidget(ChatWidget* chatWidget)
{
  connect(chatWidget, &ChatWidget::publish, this, &MainWindow::onPublish);

  m_channelTabs.addTab(chatWidget, QString("#") + chatWidget->getChannelName());
}

auto
MainWindow::getCurrentChannelWidget() -> ChatWidget*
{
  return static_cast<ChatWidget*>(m_channelTabs.currentWidget());
}

void
MainWindow::handleStorageModelUpdate()
{
  const ViewModel viewModel(m_storageModel);

  const QString currentChannel = m_channelTabs.tabText(m_channelTabs.currentIndex());

  for (int i = 0; i < m_channelTabs.count(); i++)
    m_channelTabs.widget(i)->deleteLater();

  while (m_channelTabs.count() > 0)
    m_channelTabs.removeTab(0);

  for (const auto& entry : viewModel.getChannelMap()) {

    const auto& name = entry.first;

    const auto& channel = entry.second;

    ChatWidget* widget = new ChatWidget(name, &m_channelTabs);

    widget->getChatView()->update(channel);

    addChannelWidget(widget);
  }

  for (int i = 0; i < m_channelTabs.count(); i++) {
    if (m_channelTabs.tabText(i) == currentChannel) {
      m_channelTabs.setCurrentIndex(i);
      break;
    }
  }
}

auto
MainWindow::getHash(const QByteArray& data) -> QString
{
  QCryptographicHash hash(QCryptographicHash::Sha256);
  hash.addData(data);
  return hash.result().toHex();
}

auto
MainWindow::createCurrentDirectory(const QString& workspacePath) -> QString
{
  const auto currentTime = QDate::currentDate();

  const auto currentPath = workspacePath + QDir::separator() + currentTime.toString(Qt::ISODate);

  QDir dir(currentPath);

  if (!dir.exists())
    dir.mkpath(".");

  return currentPath;
}
