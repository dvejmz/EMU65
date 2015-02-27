#ifndef LEDDISPLAYQTPROXY_H
#define LEDDISPLAYQTPROXY_H

#include <QObject>
#include <vector>
#include "../globals.h"
#include "../ui/uiproxy.h"
#include "../ui/uiproxycollection.h"

/**
 * Obtains ASCII characters and lays them out in a panel of 'm' displays with 'n' chars per display.
 */
class LedDisplayProxy : public QObject, public UiProxy
{
    Q_OBJECT
public:
    /**
     * @param numDisplays Number of displays the panel contains.
     * @param numDisplayChars Number of chars a single display can contain.
     */
    explicit LedDisplayProxy(int numDisplays, int numDisplayChars, QObject *parent = 0);
    virtual ~LedDisplayProxy();
    /**
     * Called from LedDisplay to notify a digit in the display changed so
     * the GUI LED mapped digit must be refreshed.
     */
    Q_INVOKABLE QString GetLedDisplay();
    virtual void RegisterProxy();
    void triggerDisplayDigitChanged(std::pair<int,int> displayDigitPair, byte data);
public slots:
signals:
    /**
     * Refreshes the QML GUI LED.
     */
    void displayDigitChanged();
private:
    std::vector< std::vector<byte> > m_ledDisplays;
    int m_numDisplays;
    int m_numDisplayChars;

    /**
     * Set the character that is displayed in one of the positions of the display.
     * @param displayDigitPair Pair indicating the display and specific char where the character is to be loaded.
     * @param data Byte representation of the ASCII character to load.
     */
    void SetLedDisplayChar(std::pair<int,int> displayDigitPair, byte data);
};

#endif /* LEDDISPLAYQTPROXY_H */
