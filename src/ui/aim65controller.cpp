#include "../../include/ui/aim65controller.h"

Aim65Controller::Aim65Controller(Aim65Proxy* aim65Proxy, QObject *parent) : QObject(parent)
{
    m_aimThread = std::unique_ptr<QThread>(new QThread);
    m_aim65Proxy = std::shared_ptr<Aim65Proxy>(aim65Proxy);
    m_aim65Proxy->moveToThread(m_aimThread.get());
    QObject::connect(m_aimThread.get(), SIGNAL(started()), m_aim65Proxy.get(), SLOT(Start()));
}

void Aim65Controller::Start()
{
    m_aimThread->start();
}
