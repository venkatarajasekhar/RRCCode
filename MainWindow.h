#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class RRCCore;
class Monitor;
class MonitorWrapper;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow();
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  RRCCore *rrcCore;
  Monitor *monitor;
  MonitorWrapper *monitorWrapper;
};

#endif // MAINWINDOW_H
