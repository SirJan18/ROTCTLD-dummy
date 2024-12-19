#include "rotctl_gui.h"
#include "ui_rotctl_gui.h"

ROTCTL_GUI::ROTCTL_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ROTCTL_GUI)
{
    ui->setupUi(this);

    // Connect TCP Buttons
    connect(ui->ROTCTL_TCP_RECV_START_BTN, &QPushButton::clicked, this, &ROTCTL_GUI::tcpStart);
    connect(ui->ROTCTL_TCP_RECV_STOP_BTN, &QPushButton::clicked, this, &ROTCTL_GUI::tcpStop);
}


ROTCTL_GUI::~ROTCTL_GUI()
{
    delete ui;
}


// TCP Start and Stop Slots
void ROTCTL_GUI::tcpStart()
{
    // Begin Procedure
    qDebug() << "Attempting to start TCP Server";

    // .... do stuff ...//


    // Finally Update Label
    ui->ROTCTL_TCP_RECV_STATUS_LBL->setText("Online");
}

void ROTCTL_GUI::tcpStop()
{
    // Begin Procedure
    qDebug() << "Attempting to stop TCP Server";

    // .... do stuff ...//


    // Finally Update Label
    ui->ROTCTL_TCP_RECV_STATUS_LBL->setText("Offline");
}
