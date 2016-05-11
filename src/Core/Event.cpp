#include "Event.h"

Event::Event()
{
}

Event::~Event()
{
}

bool Event::isEnabled()
{
    return this->enabled;
}

bool Event::setEnabledState(bool state)
{
    this->enabled = state;
    return (this->enabled == state);
}

time_t Event::getTimeStamp()
{
    return timestamp;
}

time_t Event::updateTimeStamp()
{
    return (timestamp = time_t(NULL));
}

bool Event::isInteractiveWith(eventType type)
{
    return this->interactions[type];
}

Event::eventType Event::getEventID()
{
	return eventID;
}

std::string Event::getDescription()
{
	return std::string();
}
