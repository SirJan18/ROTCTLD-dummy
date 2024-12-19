#ifndef ROTCTL_GUI_H
#define ROTCTL_GUI_H

#include <QMainWindow>

#include <QAbstractButton>
#include <QPushButton>

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

public slots:
    void tcpStart();
    void tcpStop();


};
#endif // ROTCTL_GUI_H
