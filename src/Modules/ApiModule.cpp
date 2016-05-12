#include "ApiModule.h"
#include "Event.h"
#include "CollisionEvent.h"
#include "MunitionEvent.h"


ApiModule::ApiModule()
{
	  inputEvent = Event::COLLISION;
	 outputEvent = Event::MUNITION;

	 Initialize("localhost", "localhost", Module::networkQueues[0], Module::networkQueues[1]);
}

ApiModule::ApiModule(std::string inHost, std::string outHost)
{
	inputEvent = Event::COLLISION;
	outputEvent = Event::MUNITION;

	Initialize(inHost, outHost, Module::networkQueues[0], Module::networkQueues[1]);
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