#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileSystemWatcher>
#include <QTabWidget>

#include "commands.h"
#include "storagemodel.h"

class MessageObject;
class ChatWidget;

class MainWindow
  : public QMainWindow
  , public CommandVisitor<char>
{
  Q_OBJECT

public:
  MainWindow(const QString& workspacePath, const QString& userName = "", QWidget* parent = nullptr);

  ~MainWindow();

  void setUserName(const QString& userName) { m_userName = userName; }

private:
  void visit(const ChannelAdditionCommand<char>&) override;

  void visit(const ChannelDeletionCommand<char>&) override;

private:
  /// Writes an object to the file system.
  ///
  /// @param object The object to write.
  void commitObject(const Object& object);

  /// Called when a message is submitted from the chat widget.
  ///
  /// @param channel The name of the channel that a message was published in.
  ///
  /// @param text The text containing the message.
  void onPublish(const QString& channel, const QString& text);

  /// Handles a message posted to the settings channel.
  ///
  /// @param text The text to be parsed that affects the settings.
  void onSettingsMessage(const QString& text);

  /// Handles a message posted to a user channel.
  ///
  /// @param channel The channel to post the text to.
  ///
  /// @param text The text to be posted to the channel.
  void onStandardMessage(const QString& channel, const QString& text);

  /// Whenever a file is created or deleted in the current directory.
  ///
  /// @param path The path to the directory that changed. Currently, this is
  ///             always the same as the current directory.
  void onDirectoryChanged(const QString& path);

  /// Gets the current channel widget, which depends on which tab is currently active.
  ///
  /// @return A pointer to the current channel widget.
  auto getCurrentChannelWidget() -> ChatWidget*;

  /// Creates a new tab for a new chat channel.
  ///
  /// @param chatWidget The new chat widget to add.
  void addChannelWidget(ChatWidget* chatWidget);

  /// Accounts for an update of the storage model by updating all channel widgets.
  void handleStorageModelUpdate();

  /// Performs a SHA-256 hash of the data.
  ///
  /// @param data The data to compute the hash of.
  ///
  /// @return A string describing the hash in base 16.
  static auto getHash(const QByteArray& data) -> QString;

  /// Creates the path for the current directory and creates the directory if it does not already exist.
  ///
  /// @param workspacePath The path that the workspace resides in.
  ///
  /// @return The path to the current date within the workspace.
  static auto createCurrentDirectory(const QString& workspacePath) -> QString;

private:
  QString m_workspacePath;

  QString m_currentPath;

  QString m_userName;

  QTabWidget m_channelTabs{ this };

  QFileSystemWatcher m_fsWatcher;

  StorageModel m_storageModel;
};

#endif // MAINWINDOW_H
