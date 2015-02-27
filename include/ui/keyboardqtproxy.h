#ifndef KEYBOARDQTPROXY_H
#define KEYBOARDQTPROXY_H

#include <QObject>
#include "../iocomponents/keyboard.h"
#include "uiproxy.h"
#include "uiproxycollection.h"

/**
 * This class intercepts keyboard events from the user so they can be
 * processed by the emulator. It also limits the keyboard keys
 * to the the AIM-65 ASCII character set.
 */
class KeyboardProxy : public QObject, public UiProxy
{
    Q_OBJECT
    Q_PROPERTY (char pressedKey
                READ GetPressedKey
                WRITE SetPressedKey)
public:
    explicit KeyboardProxy(Keyboard *keyboard, QObject *parent = 0);
    virtual ~KeyboardProxy();
    virtual void RegisterProxy();
    char GetPressedKey() const;
    void SetPressedKey(char key);
public slots:
signals:
private:
    char m_pressedKey;
    std::shared_ptr<Keyboard> m_keyboard;
};

#endif /* KEYBOARDQTPROXY_H */
