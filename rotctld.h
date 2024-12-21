#ifndef ROTCTLD_H
#define ROTCTLD_H

#include <QObject>
#include <QtNetwork/QTcpServer>


#define ROTCTL_PORT 5377

class ROTCTLD : public QObject
{
    Q_OBJECT
public:
    explicit ROTCTLD(QObject *parent = nullptr);

signals:
    // Command Related
    void tcpRecievedCommand(QString cmd);

public slots:
    void handleNewConnection();
    void handleNewConnectionData();

    // TCP Stop and start slots
    void tcpHandleStart();
    void tcpHandleStop();
    void tcpHandeTermination();

    // Command Handlers
    void tcpHandleNewCommand(QString cmd);


private:
    QTcpServer *server;
    QTcpSocket *incoming;

};

#endif // ROTCTLD_H
