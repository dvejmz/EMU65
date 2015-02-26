#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "../include/aim65.h"
#include "../include/ui/uiproxycollection.h"
#include "../include/debug/aiminspector.h"
#include "../include/ui/aim65proxy.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine mainWindow("qml/EMU65/main.qml");
    QQmlApplicationEngine aimInspectorWindow("qml/EMU65/aiminspector.qml");
    Aim65* aim65 = Aim65::GetInstance();
    Aim65Proxy* aim65Proxy = new Aim65Proxy(aim65);
    UiProxyCollection* proxyCollection = UiProxyCollection::GetInstance();

    aim65->Initialise();
    aimInspectorWindow.rootContext()->setContextProperty("aimInspector", AimInspector::GetInstance());
    mainWindow.rootContext()->setContextProperty("aim65", proxyCollection->GetAim65Proxy());
    mainWindow.rootContext()->setContextProperty("keyboard", proxyCollection->GetKeyboardProxy());
    mainWindow.rootContext()->setContextProperty("ledDisplay", proxyCollection->GetLedDisplayProxy());

    return app.exec();
}
