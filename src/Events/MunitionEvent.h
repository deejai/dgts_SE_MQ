#pragma once
#include "Event.h"

class MunitionEvent : public Event
{
public:
	unsigned const int eventID = Event::eventType::MUNITION;
    MunitionEvent();
    ~MunitionEvent();
};