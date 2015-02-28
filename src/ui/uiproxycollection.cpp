#include "../../include/ui/uiproxycollection.h"

UiProxyCollection* UiProxyCollection::m_instance = nullptr;

UiProxyCollection::UiProxyCollection()
{
}

UiProxyCollection::~UiProxyCollection()
{
}

UiProxyCollection* UiProxyCollection::GetInstance()
{
    if (UiProxyCollection::m_instance == nullptr)
    {
        UiProxyCollection::m_instance = new UiProxyCollection();
    }

    return UiProxyCollection::m_instance;
}

void UiProxyCollection::InsertLedDisplayProxy(std::shared_ptr<LedDisplayProxy> proxy)
{
    this->m_ledProxy = std::shared_ptr<LedDisplayProxy>(proxy);
}

void UiProxyCollection::InsertKeyboardProxy(std::shared_ptr<KeyboardProxy> proxy)
{
    this->m_keyboardProxy = std::shared_ptr<KeyboardProxy>(proxy);
}

void UiProxyCollection::InsertAim65Proxy(std::shared_ptr<Aim65Proxy> proxy)
{
    this->m_aim65Proxy = std::shared_ptr<Aim65Proxy>(proxy);
}

LedDisplayProxy* UiProxyCollection::GetLedDisplayProxy()
{
    return this->m_ledProxy.get();
}

KeyboardProxy* UiProxyCollection::GetKeyboardProxy()
{
    return this->m_keyboardProxy.get();
}

Aim65Proxy* UiProxyCollection::GetAim65Proxy()
{
    return this->m_aim65Proxy.get();
}
