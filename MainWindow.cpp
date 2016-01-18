#include "MainWindow.h"
#include <UI/UIModel.h>
#include <UI/UIView.h>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QShortcut>
#include <RRCConfig/RRCConfig.h>
#include <RRCCore/RRCCore.h>
#include <Monitor/Monitor.h>
#include <Monitor/MonitorWrapper.h>

MainWindow::MainWindow() {
    UIModel *model = new UIModel(this);
    model->SetSceneSize();
    model->AddObstacles();

    UIView *viewer = new UIView(model, this);
    monitor = new Monitor(model, RRCCore::Instance());
    monitorWrapper = new MonitorWrapper(monitor);

    setWindowTitle("RRC");

    QPushButton *run = new QPushButton(this);
    run->setText("Run");

    QLabel *labelNumSteps = new QLabel("Number of Steps:", this);

    QLineEdit *lineEditNumSteps = new QLineEdit(this);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(run, 0, 0);
    layout->addWidget(labelNumSteps, 0, 1);
    layout->addWidget(lineEditNumSteps, 0, 2);
    layout->addWidget(viewer, 1, 0, 3, 3);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

    //  make the buttons do things
    connect(run, SIGNAL(clicked()), model, SLOT(slot_run()));
}

MainWindow::~MainWindow() {
    delete monitor;
    delete monitorWrapper;
}
