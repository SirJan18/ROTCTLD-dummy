#ifndef ROTCTLD_H
#define ROTCTLD_H

#include <QObject>

class ROTCTLD : public QObject
{
    Q_OBJECT
public:
    explicit ROTCTLD(QObject *parent = nullptr);

signals:
};

#endif // ROTCTLD_H
