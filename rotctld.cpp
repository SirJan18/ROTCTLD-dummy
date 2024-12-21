#include "rotctld.h"

#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QStringList>

ROTCTLD::ROTCTLD(QObject *parent)
    : QObject{parent}
{

    server = new QTcpServer();

    // Bind new connection event
    connect(server, &QTcpServer::pendingConnectionAvailable, this, &ROTCTLD::handleNewConnection );

    // Connect command processing
    connect(this, &ROTCTLD::tcpRecievedCommand, this, &ROTCTLD::tcpHandleNewCommand);
}


// Handle start and stop buttons
void ROTCTLD::tcpHandleStart()
{
    qDebug() << "Starting TCP Server connections";
    // server->resumeAccepting();
    if (!server->listen(QHostAddress::Any, ROTCTL_PORT) )
    {
        qCritical() << "Failed to initate TCP Server on socket: " << ROTCTL_PORT;
        qCritical() << "Error: " << server->errorString();
    }

}
void ROTCTLD::tcpHandleStop()
{
    // Stop Accepting new connections
    server->pauseAccepting();
    server->close();
    qDebug() << "Stopped Accepting Connections";

    if (incoming->state() >= QAbstractSocket::ConnectedState)
    {
        qDebug() << "Closing active socket";
        // disconnect and close current connection
        disconnect( incoming, &QTcpSocket::readyRead, this, &ROTCTLD::handleNewConnectionData );
        disconnect( incoming, &QAbstractSocket::disconnected, this, &ROTCTLD::tcpHandeTermination );
        incoming->disconnect();
        incoming->close();
    };
}

void ROTCTLD::handleNewConnection()
{
    incoming = server->nextPendingConnection();
    qInfo() << "Recieved connetion from " << incoming->localAddress();

    // Connect new message at socket with message handler
    connect( incoming, &QTcpSocket::readyRead, this, &ROTCTLD::handleNewConnectionData ) ;
    connect ( incoming, &QAbstractSocket::disconnected, this, &ROTCTLD::tcpHandeTermination );
}
void ROTCTLD::tcpHandeTermination()
{
    qDebug() << "Socket has been terminated";
    incoming->close();
}

void ROTCTLD::handleNewConnectionData()
{
    QByteArray data = incoming->readLine();
    QString cmd = QString::fromUtf8(data).trimmed();
    emit( tcpRecievedCommand(cmd) );
}

void ROTCTLD::tcpHandleNewCommand(QString cmd)
{
    QStringList commandSegments = cmd.split(' ', Qt::SkipEmptyParts);
    qDebug() << "Parsing on: " << commandSegments.at(0);
    return;
}
