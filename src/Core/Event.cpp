#include "Event.h"

Event::Event()
{
}

Event::~Event()
{
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
    return interactions[type];
}

Event::eventType Event::getEventID()
{
	return eventID;
}

std::string Event::getDescription()
{
	return std::string();
}
