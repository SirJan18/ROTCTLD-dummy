#include "rotctld.h"
#include "rotctlreader.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

// Q_LOGGING_CATEGORY(networkCategory, "RotodCTL.network", QtDebugMsg)


rotctld::rotctld(QObject *parent)
    : QObject{parent}
{
    // Connect socket has new connection signal
    qInfo() << "ROTCTLD has been initialized";

    sock = new QTcpServer();
    // Connect Signal for initialized socket
    connect(sock, &QTcpServer::newConnection, this, &rotctld::handleNewConnection);
    connect(this, &rotctld::recievedCommand, this, &rotctld::handleNewCommand);
}

rotctld::~rotctld()
{
    sock->close();
}

void rotctld::initializeSocket()
{
    qInfo() << "New socket request recieved";

    if (!sock->listen(QHostAddress::Any, 5733))
    {
        qCritical() << "Could not start TCP Server";
    } else {
        qInfo() << "Started TCP Server on port: 5733";
    }

}

void rotctld::closeSocket()
{
    if (incoming != nullptr)
    {
        qDebug() << "Previous incoming socket has been closed";
        incoming->close();
    }
    incoming = nullptr;

    // Stop Accepting new connections
    if (sock->isListening())
        sock->close();
}

void rotctld::handleNewConnection()
{
    qInfo() << "New connection has been recieved";
    // If socket has been previously opened, close it
    if (incoming != nullptr)
    {
        qWarning() << "A connection is already active. Closing the previous connection.";
        incoming->close();
        incoming->deleteLater();
    }
    // Reassign to new connection
    incoming = sock->nextPendingConnection();

    if (incoming)
    {
        connect(incoming, &QTcpSocket::readyRead, this, &rotctld::readData, Qt::QueuedConnection);
        connect(incoming, &QTcpSocket::disconnected, this, &rotctld::onClientDC, Qt::QueuedConnection);
        qInfo() << "Connection established with client:" << incoming->peerAddress().toString();
    }
}

void rotctld::onClientDC()
{
    qInfo() << "Client disconnected.";
    incoming->deleteLater();
    incoming = nullptr;
}

void rotctld::readData()
{
    while(incoming->bytesAvailable() > 0)
    {
        QByteArray data = incoming->readLine();
        QString message = QString::fromUtf8(data).trimmed();
        qDebug() << "Received Message:" << message;
        emit recievedCommand(message);
    }
}

void rotctld::writeData(QString cmd)
{
    QByteArray cmd_arr = cmd.toUtf8();
    incoming->write(cmd_arr);
    qDebug() << cmd;
}
void rotctld::handleNewCommand(QString cmd)
{
    rotoctlTools::RotatorCommandTypes type = rotoctlTools::determineMessageType(cmd.toStdString());

    if (type == rotoctlTools::RotatorCommandTypes::GetPosition)
    {
        qDebug() << "Recieved positon request";

        emit commandGetPos();
    }
    else if (type == rotoctlTools::RotatorCommandTypes::SetPosition)
    {
        double az, el;
        QStringList parts = cmd.split(' ', Qt::SkipEmptyParts);
        az = parts[1].toDouble();
        el = parts[2].toDouble();
        emit ( commandSetPos(float(az), float(el)));
        emit ( writeData( QString("RPRT %0\n").arg(0) ) );

    } else {
        qDebug() << "Ya Shit's busted";
    }
}

void rotctld::sendPosition(float az, float el)
{
    // Implement string creation
    QString cmd = QString("%1 %2").arg(az, 0, 'f', 5).arg(el, 0, 'f', 5);

    emit( writeData( QString("%1\n").arg(az, 0, 'f', 3) ) );
    emit( writeData( QString("%1\n").arg(el, 0, 'f', 3) ) );

}

