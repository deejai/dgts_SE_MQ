#include "PhysicsModule.h"
#include "Event.h"

physicsModule::physicsModule()
{
	 inputEvent = Event::PHYSICS;
	outputEvent = Event::INSTRUCTION;
}

physicsModule::~physicsModule()
{
}
