#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

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
  std::unique_ptr<Monitor> m_monitor;
  std::unique_ptr<MonitorWrapper> m_monitorWrapper;
};

#endif // MAINWINDOW_H
