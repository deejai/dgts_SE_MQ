#pragma once
#include "Event.h"

class MunitionEvent : public Event
{
public:
    MunitionEvent();
    ~MunitionEvent();

	static Event *stringToEvent(std::string evtString);
};