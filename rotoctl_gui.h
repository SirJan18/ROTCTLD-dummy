#ifndef ROTOCTL_GUI_H
#define ROTOCTL_GUI_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>

#include "rotctld.h"

#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QLoggingCategory>
#include <qlogging.h>


Q_DECLARE_LOGGING_CATEGORY(networkCategory)

QT_BEGIN_NAMESPACE
namespace Ui {
class ROTOCTL_GUI;
}
QT_END_NAMESPACE

class ROTOCTL_GUI : public QMainWindow
{
    Q_OBJECT

public:
    ROTOCTL_GUI(QWidget *parent = nullptr);
    ~ROTOCTL_GUI();

    QThread *thread;
    rotctld *worker;

public slots:
    void onServerChangeRequest(QAbstractButton *button);
    void handleNewCommand(QString cmd);

    // rotctld commands
    void handleGetPos();
    void handleSetPos(float az, float el);

signals:
    void startConnection();
    void endConnection();

    void sendPos(float az, float el);

private:
    Ui::ROTOCTL_GUI *ui;

};
#endif // ROTOCTL_GUI_H
