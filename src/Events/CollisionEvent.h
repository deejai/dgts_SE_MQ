#pragma once
#include "Event.h"

class CollisionEvent : public Event
{
public:
    unsigned const int eventID = Event::eventType::COLLISION;
    CollisionEvent();
    ~CollisionEvent();
};

