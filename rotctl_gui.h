#ifndef ROTCTL_GUI_H
#define ROTCTL_GUI_H

#include <QMainWindow>

#include <QAbstractButton>
#include <QPushButton>

#include "rotctld.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ROTCTL_GUI;
}
QT_END_NAMESPACE

class ROTCTL_GUI : public QMainWindow
{
    Q_OBJECT

public:
    ROTCTL_GUI(QWidget *parent = nullptr);
    ~ROTCTL_GUI();

private:
    Ui::ROTCTL_GUI *ui;
    QThread *worker_thread;
    ROTCTLD *worker_instance;

public slots:
    void tcpStart();
    void tcpStop();

    void rotctlLog(QString data);

signals:
    void tcpStartSignal();
    void tcpStopSignal();


};
#endif // ROTCTL_GUI_H
