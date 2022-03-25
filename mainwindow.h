#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileSystemWatcher>

#include "centralwidget.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(const QString& workspacePath = ".", QWidget* parent = nullptr);

  ~MainWindow();

private:
  void onPublish(const Message& message);

  /// Whenever a file is created or deleted in the current directory.
  void onDirectoryChanged(const QString&);

  static auto getHash(const QByteArray& data) -> QString;

  /// Creates the path for the current directory and creates the directory if it does not already exist.
  static auto createCurrentDirectory(const QString& workspacePath) -> QString;

private:
  CentralWidget m_centralWidget{ this };

  QString m_workspacePath;

  QString m_currentPath;

  QFileSystemWatcher m_fsWatcher;
};

#endif // MAINWINDOW_H
