#include "Emitter.hpp"

Emitter::Emitter() {}

const char *Emitter::id()
{
  return (const char *)_id;
}

void Emitter::clear()
{
  _listeners.clear();
}

void Emitter::setId(const char *id)
{
  strncpy(_id, id, 100);
}

void Emitter::addListener(listener_struct listener)
{
  _listeners.push_back(listener);
}

void Emitter::removeListener(int listenerId)
{
  for (size_t j = 0; j < _listeners.size(); j += 1)
  {
    if (_listeners[j].id == listenerId)
    {
      _listeners.erase(_listeners.begin() + j);
      break;
    }
  }
}

void Emitter::emit(const char *value)
{
  for (size_t i = 0; i < _listeners.size(); i += 1)
    _listeners[i].listener(_id, value);
}