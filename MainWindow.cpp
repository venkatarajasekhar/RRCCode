#include "MainWindow.h"
#include <UI/UIModel.h>
#include <UI/UIView.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QShortcut>
#include <QComboBox>
#include <QString>
#include <QPainter>
#include <QStatusBar>
#include <QPixmap>
#include <RRCCore/RRCCore.h>
#include <Monitor/Monitor.h>
#include <Monitor/MonitorWrapper.h>

MainWindow::MainWindow() {
    setWindowTitle("RRC");

    QPushButton *run = new QPushButton(this);
    run->setText("Run");
    QPushButton *reset = new QPushButton(this);
    reset->setText("Reset");

    QLabel *labelNumSteps = new QLabel("Number of Steps:", this);
    QLabel *labelStartPosLegend = new QLabel(this);
    QLabel *labelStartPos = new QLabel("StartPos: ", this);
    QLabel *labelGoalPos = new QLabel("GoalPos: ", this);
    QLabel *labelGoalPosLegend = new QLabel(this);

    // status bar
    QStatusBar *statusBar = new QStatusBar(this);
    QLabel *labelStatus = new QLabel("Node Generated: ", this);
    QLabel *labelCurrNumNodes = new QLabel("0", this);
    statusBar->addPermanentWidget(labelStatus);
    statusBar->addPermanentWidget(labelCurrNumNodes);

    // draw startpos and goalpos legend
    int pixMapWidth = 20;
    int pixMapHeight = 20;
    QPixmap pixmap(pixMapWidth,pixMapHeight);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    painter.setBrush(QBrush(Qt::yellow));
    painter.drawEllipse(0,0,pixMapWidth,pixMapHeight);
    labelStartPosLegend->setPixmap(pixmap);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(0,0,pixMapWidth,pixMapHeight);
    labelGoalPosLegend->setPixmap(pixmap);
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(labelStartPos);
    hBoxLayout->addWidget(labelStartPosLegend);
    hBoxLayout->addWidget(labelGoalPos);
    hBoxLayout->addWidget(labelGoalPosLegend);

    QSpinBox *spinBoxNumSteps = new QSpinBox(this);
    spinBoxNumSteps->setRange(0, 100000);

    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItem("RRT");
    comboBox->addItem("RRT*");
    comboBox->addItem("RRC");

    UIModel *model = new UIModel(this, comboBox, spinBoxNumSteps, run, reset, labelCurrNumNodes);
    model->SetSceneSize();
    model->AddObstacles();

    UIView *viewer = new UIView(model, this);
    m_RRCCore = std::unique_ptr<RRCCore>(new RRCCore());
    m_monitor = std::unique_ptr<Monitor>(new Monitor(model, m_RRCCore.get()));
    m_monitorWrapper = std::unique_ptr<MonitorWrapper>(new MonitorWrapper(m_monitor.get()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(run, 0, 0);
    layout->addWidget(reset, 0, 1);
    layout->addWidget(labelNumSteps, 0, 3);
    layout->addWidget(spinBoxNumSteps, 0, 4);
    layout->addWidget(comboBox, 1, 0);
    layout->addLayout(hBoxLayout,1,1,1,2);
    layout->addWidget(statusBar, 1, 4);
    layout->addWidget(viewer, 2, 0, 5, 5);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

    //  make the buttons do things
    connect(run, SIGNAL(clicked()), model, SLOT(slot_run()));
    connect(reset, SIGNAL(clicked()), model, SLOT(slot_reset()));
}

MainWindow::~MainWindow() {

}
