#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QProcess>
#include <QTranslator>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

namespace {

const char* g_styleSheet = R"(
QWidget {
  border-width: 0px;
}

QWidget#ChatView {
  color: black;
  background-color: white;
}

QTextEdit {
  color: black;
  background-color: white;
  border-radius: 5px;
  border-width: 1px;
  padding: 5px;
}

QWidget#ChatView QLabel {
  background-color: white;
  border-radius: 5px;
  border-width: 1px;
  padding: 5px;
}
)";

} // namespace

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  a.setApplicationName(QObject::tr("Chats"));

  a.setStyleSheet(g_styleSheet);

  QTranslator translator;

  const QStringList uiLanguages = QLocale::system().uiLanguages();

  for (const QString& locale : uiLanguages) {
    const QString baseName = "chats_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  MainWindow w(".");

  w.showMaximized();

#ifdef Q_OS_WIN
  char acUserName[MAX_USERNAME];

  DWORD nUserName = sizeof(acUserName);

  if (GetUserName(acUserName, &nUserName))
    w.setUserName(acUserName);
#elif defined(Q_OS_UNIX)
  QProcess process;
  QObject::connect(&process,
                   static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                   [&process, &w](int exitCode, QProcess::ExitStatus exitStatus) {
                     const QString userName(process.readAllStandardOutput());
                     w.setUserName(userName);
                   });
  process.start("whoami", QStringList() << "whoami");
#endif

  return a.exec();
}
