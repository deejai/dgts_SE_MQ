#include "ApiModule.h"
#include "Event.h"


ApiModule::ApiModule()
{
	  inputEvent = Event::COLLISION;
	 outputEvent = Event::MUNITION;
}

ApiModule::~ApiModule()
{
}

CollisionEvent *ApiModule::processEvent(MunitionEvent *evt)
{
	delete evt;
	return new CollisionEvent();
}