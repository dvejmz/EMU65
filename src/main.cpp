#include <QObject>
#include <QThread>
#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "../include/aim65.h"
#include "../include/ui/uiproxycollection.h"
#include "../include/debug/aiminspector.h"
#include "../include/ui/aim65proxy.h"
#include "../include/ui/aim65controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine mainWindow("qml/EMU65/main.qml");
    QQmlApplicationEngine aimInspectorWindow("qml/EMU65/aiminspector.qml");
    UiProxyCollection* proxyCollection = UiProxyCollection::GetInstance();
    Aim65Proxy* aim65Proxy = new Aim65Proxy(Aim65::GetInstance());
    //Aim65Controller* aim65Controller = new Aim65Controller(aim65Proxy);

    QThread aimThread;
    aim65Proxy->moveToThread(&aimThread);
    QObject::connect(&aimThread, SIGNAL(started()), aim65Proxy, SLOT(Start()));
    aimThread.start();
    aimInspectorWindow.rootContext()->setContextProperty("aimInspector", AimInspector::GetInstance());
    mainWindow.rootContext()->setContextProperty("aim65", proxyCollection->GetAim65Proxy());
    //mainWindow.rootContext()->setContextProperty("aim65Controller", aim65Controller);
    mainWindow.rootContext()->setContextProperty("keyboard", proxyCollection->GetKeyboardProxy());
    mainWindow.rootContext()->setContextProperty("ledDisplay", proxyCollection->GetLedDisplayProxy());

    return app.exec();
}
