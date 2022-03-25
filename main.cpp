#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

namespace {

const char* g_styleSheet = R"(
QMainWindow {
  background: #114B5F
}

QFrame#TopWidget {
  background: #156079
}

QFrame#CentralWidget {
}

QFrame#BodyWidget {

}

QFrame#LeftPanel {
}

QLabel {
  border: 1px;
  border-color: #186E8B;
  color: white
}

QFrame#ChatWidget {
  background: white
}
)";

} // namespace

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  a.setApplicationName("Chats");

  QTranslator translator;

  const QStringList uiLanguages = QLocale::system().uiLanguages();

  for (const QString& locale : uiLanguages) {
    const QString baseName = "chats_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  MainWindow w;

  a.setStyleSheet(g_styleSheet);

  w.showMaximized();

  return a.exec();
}
