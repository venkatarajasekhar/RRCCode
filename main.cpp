#include "MainWindow.h"
#include <QApplication>
#include <Thread/ScopedThread.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  ScopedThread uiThread((std::thread((w.show()))));

  return a.exec();
}
