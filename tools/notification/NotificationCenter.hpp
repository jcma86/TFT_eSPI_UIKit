#ifndef __TOOLS_NOTIFICATION_CENTER__
#define __TOOLS_NOTIFICATION_CENTER__

#include <Arduino.h>
#include <string.h>
#include <vector>
#include <functional>

#include "Emitter.hpp"

class NotificationCenter
{
private:
  int _listenersCount = 0;
  std::vector<Emitter*> _emitters;

  int findEmitterId(const char *emitterId);

  NotificationCenter();
  ~NotificationCenter();

public:
  static NotificationCenter &getNotificationCenter()
  {
    static NotificationCenter ncInstance;
    return ncInstance;
  }

  NotificationCenter(NotificationCenter const &) = delete;
  NotificationCenter &operator=(const NotificationCenter &) = delete;

  Emitter *createEmitter(const char *id);
  int subscribe(const char *emitterId, std::function<void(const char *emitterId, const char *value)> listener);
  void unsubscribe(const char *emitterId, int listenerId);
};

#endif
