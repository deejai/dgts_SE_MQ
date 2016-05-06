#pragma once
#include "Event.h"

class PhysicsEvent : public Event
{
public:
	unsigned const int eventID = Event::eventType::PHYSICS;
    PhysicsEvent();
    ~PhysicsEvent();
};

