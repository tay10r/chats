#include "mainwindow.h"

#include "message.h"

#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(const QString& workspacePath, QWidget* parent)
  : QMainWindow(parent)
  , m_workspacePath(workspacePath)
  , m_currentPath(createCurrentDirectory(m_workspacePath))
  , m_fsWatcher(QStringList(m_currentPath), this)
{
  setCentralWidget(&m_centralWidget);

  auto* chatInput = m_centralWidget.getBodyWidget()->getChatWidget()->getChatInput();

  connect(chatInput, &ChatInput::publish, this, &MainWindow::onPublish);

  connect(&m_fsWatcher, &QFileSystemWatcher::directoryChanged, this, &MainWindow::onDirectoryChanged);
}

MainWindow::~MainWindow() {}

void
MainWindow::onPublish(const Message& message)
{
  const auto jsonData = message.toJson();

  const auto hash = getHash(jsonData);

  const auto path = m_workspacePath + QDir::separator() + hash + ".json";

  QFileInfo fileInfo(path);

  if (fileInfo.exists()) {
    // TODO : error message
    return;
  }

  QFile file(path);

  if (!file.open(QIODevice::WriteOnly)) {
    // TODO : error message
  } else {

    file.write(jsonData);

    auto* chatInput = m_centralWidget.getBodyWidget()->getChatWidget()->getChatInput();

    chatInput->clear();
  }
}

void
MainWindow::onDirectoryChanged(const QString& path)
{
  auto* chatView = m_centralWidget.getBodyWidget()->getChatWidget()->getChatView();

  chatView->scanDirectory(path);
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
  const auto currentPath = workspacePath + QDir::separator() + QDateTime::currentDateTime().toString();

  QDir dir(currentPath);
  if (!dir.exists())
    dir.mkpath(".");

  return currentPath;
}
