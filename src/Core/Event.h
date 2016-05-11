#pragma once
#include <time.h>
#include <iostream>

class Event
{
public:
    Event();
    ~Event();

    // eventType::NUM_TYPES gives the number of different Event types
    enum eventType { COLLISION, MUNITION, PHYSICS, NUM_TYPES };

    // Disabled Events will be passed along without processing by EventHandler objects
    bool isEnabled();
    bool setEnabledState(bool state); // Returns true is state changed

    time_t getTimeStamp();
    time_t updateTimeStamp(); // Returns modified timestamp

    bool isInteractiveWith(Event::eventType type);

private:
    bool enabled = true;
    time_t timestamp = time(NULL);

protected:
    Event::eventType eventID;
    bool interactions[Event::eventType::NUM_TYPES];
};