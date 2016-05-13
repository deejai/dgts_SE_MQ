#include "Event.h"
#include "CollisionEvent.h"
#include "MunitionEvent.h"
#include "PhysicsEvent.h"
#include "InstructionEvent.h"
#include <ctype.h>

std::mutex Event::m_mutex;

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

Event * Event::stringToEvent(std::string str)
{
	int type;
	Event *evt = nullptr;

	if (str.length() > 10 && !str.substr(0, 10).compare("eventType_") ){
		if (isdigit(str[10])) {
			type = str[10] - '0';
			if (type < Event::NUM_TYPES ){
				m_mutex.lock();
				switch (type)
				{
				case Event::COLLISION:
					evt = new CollisionEvent();
					break;

				case Event::MUNITION:
					evt = new MunitionEvent();
					break;

				case Event::PHYSICS:
					evt = new PhysicsEvent();
					break;

				case Event::INSTRUCTION:
					evt = new InstructionEvent();
					break;

				default:
					std::cout << "Something went wrong. Received: eventType_" << type << "\n";
					break;
				}
			}
		}
	}
	m_mutex.unlock();
	return evt;
}
