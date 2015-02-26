#ifndef UIPROXY_H
#define UIPROXY_H

#include "../globals.h"
#include "uiproxycollection.h"

class UiProxy
{
public:
  UiProxy();
  virtual ~UiProxy();
protected:
  virtual void RegisterProxy() = 0;

  DISALLOW_COPY_AND_ASSIGN(UiProxy);
};

#endif /* UIPROXY_H */
