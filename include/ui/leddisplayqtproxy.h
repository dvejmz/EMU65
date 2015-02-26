#ifndef LEDDISPLAYQTPROXY_H
#define LEDDISPLAYQTPROXY_H

#include <QObject>
#include <vector>
#include "../globals.h"
#include "../ui/uiproxy.h"
#include "../ui/uiproxycollection.h"

class LedDisplayProxy : public QObject, public UiProxy
{
    Q_OBJECT
public:
    explicit LedDisplayProxy(int numDisplays, int numDisplayChars, QObject *parent = 0);
    virtual ~LedDisplayProxy();
    /**
     * @brief DisplayDigitChanged
     * {Called from LedDisplay to notify a digit in the display changed so
     * the GUI LED mapped digit must be refreshed.}
     */
    Q_INVOKABLE QString GetLedDisplay();
    virtual void RegisterProxy();
    void triggerDisplayDigitChanged(std::pair<int,int> displayDigitPair, byte data);
public slots:
signals:
    void displayDigitChanged(); // Refreshes the QML GUI LED.
private:
    std::vector< std::vector<byte> > m_ledDisplays;
    int m_numDisplays;
    int m_numDisplayChars;

    void SetLedDisplayChar(std::pair<int,int> displayDigitPair, byte data);
};

#endif /* LEDDISPLAYQTPROXY_H */
