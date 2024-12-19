#ifndef ROTCTLD_H
#define ROTCTLD_H

#include <QObject>

#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>

#include <QLoggingCategory>
#include <qlogging.h>

// Q_DECLARE_LOGGING_CATEGORY(socketCategory)

class rotctld : public QObject
{
    Q_OBJECT
public:
    explicit rotctld(QObject *parent = nullptr);
    ~rotctld();

signals:
    void recievedCommand(QString cmd);

    // rotctl commands
    void commandGetPos();
    void commandSetPos(float az, float el);

public slots:
    void handleNewConnection();
    void handleNewCommand(QString cmd);
    void closeSocket();
    void readData();
    void onClientDC();
    void writeData(QString cmd);

    void sendPosition(float az, float el);

    /**
     * @brief initializeSocket Creates and binds TCP Server to port
     * This function creates the new TCP Server and beings listening on
     * the proper rotctl net port
     */
    void initializeSocket();

private:
    QTcpServer *sock = nullptr;
    QTcpSocket *incoming = nullptr;



};

#endif // ROTCTLD_H
