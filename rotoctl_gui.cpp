#include <QThread>

#include "rotoctl_gui.h"
#include "ui_rotoctl_gui.h"
#include "rotctld.h"

// Q_LOGGING_CATEGORY(networkCategory, "RotoCTLGui.network", QtDebugMsg)


ROTOCTL_GUI::ROTOCTL_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ROTOCTL_GUI)
{
    ui->setupUi(this);

    // Create new thtread and worker
    thread = new QThread(this);
    worker = new rotctld();
    // Move to new thread
    worker->moveToThread(thread);

    // Connect dialog button press
    connect(ui->rotctl_emulator_statusBtn, &QDialogButtonBox::clicked, this, &ROTOCTL_GUI::onServerChangeRequest);

    // Connect Thread start and end
    // connect(thread, &QThread::started, worker, &rotctld::initializeSocket);
    // connect(this, &QObject::destroyed, thread, &QThread::quit);

    // Connect button presses
    // - Bind start connection
    connect(this, &ROTOCTL_GUI::startConnection, worker, &rotctld::initializeSocket, Qt::QueuedConnection);
    // - Bind end connection
    connect(this, &ROTOCTL_GUI::endConnection, worker, &rotctld::closeSocket, Qt::QueuedConnection);

    // Bind recieved Command
    connect(worker, &rotctld::recievedCommand, this, &ROTOCTL_GUI::handleNewCommand, Qt::QueuedConnection);
    // Bind sent Commands
    connect(worker, &rotctld::writeData, this, &ROTOCTL_GUI::handleNewCommand, Qt::QueuedConnection);

    // Bind seperate commands
    connect(worker, &rotctld::commandGetPos, this, &ROTOCTL_GUI::handleGetPos, Qt::QueuedConnection);
    connect(this, &ROTOCTL_GUI::sendPos, worker, &rotctld::sendPosition, Qt::QueuedConnection);

    connect(worker, &rotctld::commandSetPos, this, &ROTOCTL_GUI::handleSetPos, Qt::QueuedConnection);

    thread->start();
}

ROTOCTL_GUI::~ROTOCTL_GUI()
{
    delete ui;
}

void ROTOCTL_GUI::onServerChangeRequest(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton sb = ui->rotctl_emulator_statusBtn->standardButton(button);
    switch (sb) {
        case QDialogButtonBox::Ok:
            // Handle ok
            ui->rotctl_logs->append("Initializing server connection...");
            qDebug() << "Emitting start connection";
            emit startConnection();
            ui->rotctl_statusBox->setText("ROTCTL Emulator: Online");
            break;
        case QDialogButtonBox::Cancel:
            // Handle cancel
            emit endConnection();
            qDebug() << "Emitting end connection";
            ui->rotctl_logs->append("Termindated server connection...");
            ui->rotctl_statusBox->setText("ROTCTL Emulator: Offline");
            break;
        default:
            break;
    }
}

void ROTOCTL_GUI::handleGetPos()
{
    emit sendPos(ui->azimuth_number->value(), ui->elevation_number->value() );
}

void ROTOCTL_GUI::handleSetPos(float az, float el)
{
    ui->azimuth_number->display(az);
    ui->elevation_number->display(el);
}


void ROTOCTL_GUI::handleNewCommand(QString cmd)
{
    ui->rotctl_logs->append(cmd);
}
