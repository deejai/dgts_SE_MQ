#include "ApiModule.h"
#include "Event.h"
#include "CollisionEvent.h"
#include "MunitionEvent.h"


ApiModule::ApiModule()
{
	  inputEvent = Event::COLLISION;
	 outputEvent = Event::MUNITION;

	 Initialize("localhost", "localhost");
}

ApiModule::~ApiModule()
{
}

Event *ApiModule::processEvent(Event *evt)
{
	if (evt->getEventID() == inputEvent) {
		delete evt;
		return new CollisionEvent();
	}
	else {
		// Wrong Event type
		delete evt;
		// TODO: Call Module error function
		return nullptr;
	}
}