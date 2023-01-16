#ifndef __TOOLS_NOTIFICATION_CENTER_EMITTER__
#define __TOOLS_NOTIFICATION_CENTER_EMITTER__

#include <Arduino.h>
#include <vector>
#include <functional>

typedef struct
{
  int id;
  std::function<void(const char *emitterId, const char *value)> listener;
} listener_struct;

class Emitter
{
private:
  char _id[100];
  std::vector<listener_struct> _listeners;

public:
  Emitter();

  const char *id();
  void clear();
  void setId(const char *id);
  void addListener(listener_struct listener);
  void removeListener(int listenerId);
  void emit(const char *value);
};

#endif