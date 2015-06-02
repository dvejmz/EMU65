#ifndef AIM65CONTROLLER_H
#define AIM65CONTROLLER_H

#include <memory>
#include <QObject>
#include <QThread>
#include "../include/ui/aim65proxy.h"

class Aim65Controller : public QObject
{
    Q_OBJECT
public:
    Aim65Controller(Aim65Proxy *aim65, QObject *parent = 0);
public slots:
    void Start();
signals:
private:
    std::unique_ptr<QThread> m_aimThread;
    std::shared_ptr<Aim65Proxy> m_aim65Proxy;
};

#endif /* AIM65CONTROLLER_H */
