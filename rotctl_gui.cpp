#include "rotctl_gui.h"
#include "ui_rotctl_gui.h"

#include <qthread.h>

ROTCTL_GUI::ROTCTL_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ROTCTL_GUI)
{
    ui->setupUi(this);
    // Create new worker thread
    worker_thread = new QThread(this);
    worker_instance = new ROTCTLD();
    worker_instance->moveToThread(worker_thread);

    // Connect TCP Menu Buttons
    connect(ui->ROTCTL_TCP_RECV_START_BTN, &QPushButton::clicked, this, &ROTCTL_GUI::tcpStart);
    connect(ui->ROTCTL_TCP_RECV_STOP_BTN, &QPushButton::clicked, this, &ROTCTL_GUI::tcpStop);

    // Connect TcpServer Signals
    connect(this, &ROTCTL_GUI::tcpStartSignal, worker_instance, &ROTCTLD::tcpHandleStart, Qt::QueuedConnection);
    connect(this, &ROTCTL_GUI::tcpStopSignal, worker_instance, &ROTCTLD::tcpHandleStop, Qt::QueuedConnection);

    // Connect recieving logging
    connect(worker_instance, &ROTCTLD::tcpRecievedCommand, this, &ROTCTL_GUI::rotctlLog);

    // Start Worker Thread
    worker_thread->start();
}


ROTCTL_GUI::~ROTCTL_GUI()
{
    delete ui;

    // Handle thread termination
    worker_thread->quit();
    worker_thread->wait();

    delete worker_instance;
}


// TCP Start and Stop Slots
void ROTCTL_GUI::tcpStart()
{
    // Begin Procedure
    qDebug() << "Attempting to start TCP Server";

    // .... do stuff .... //
    emit ( tcpStartSignal() );

    // Finally Update Label
    ui->ROTCTL_TCP_RECV_STATUS_LBL->setText("Online");
}

void ROTCTL_GUI::tcpStop()
{
    // Begin Procedure
    qDebug() << "Attempting to stop TCP Server";

    // .... do stuff .... //
    emit ( tcpStopSignal() );

    // Finally Update Label
    ui->ROTCTL_TCP_RECV_STATUS_LBL->setText("Offline");
}

void ROTCTL_GUI::rotctlLog(QString data)
{
    ui->ROTCTL_LOG->append(data);
}
