#include "../../include/ui/keyboardqtproxy.h"

KeyboardProxy::KeyboardProxy(Keyboard *keyboard, QObject *parent) : QObject(parent), UiProxy()
{
    this->m_keyboard = std::shared_ptr<Keyboard>(keyboard);
    this->RegisterProxy();
}

KeyboardProxy::~KeyboardProxy()
{
}

void KeyboardProxy::RegisterProxy()
{
    UiProxyCollection::GetInstance()->InsertKeyboardProxy(std::shared_ptr<KeyboardProxy>(this));
}

char KeyboardProxy::GetPressedKey() const
{
    return this->m_pressedKey;
}

void KeyboardProxy::SetPressedKey(char key)
{
    this->m_pressedKey = key;
    this->m_keyboard->onKeyPressed(key);
}


