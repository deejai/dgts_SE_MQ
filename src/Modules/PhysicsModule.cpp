#include "PhysicsModule.h"
#include "Event.h"
#include "PhysicsEvent.h"
#include "InstructionEvent.h"

PhysicsModule::PhysicsModule()
{
	inputEvent = Event::PHYSICS;
	outputEvent = Event::INSTRUCTION;

	Initialize("localhost", "localhost", Module::networkQueues[2], Module::networkQueues[3]);
}

PhysicsModule::PhysicsModule(std::string inHost, std::string outHost)
{
	inputEvent = Event::PHYSICS;
	outputEvent = Event::INSTRUCTION;

	Initialize(inHost, outHost, Module::networkQueues[2], Module::networkQueues[3]);
}

PhysicsModule::~PhysicsModule()
{
}

Event *PhysicsModule::processEvent(Event *evt)
{
	if (evt->getEventID("processEvent:physicsMod") == inputEvent) {
		delete evt;

		// Avoid race condition
		Event::m_mutex.lock();
		evt = new InstructionEvent();
		Event::m_mutex.unlock();

		return evt;
	}
	else {
		// Wrong Event type
		delete evt;
		// TODO: Call Module error function
		return nullptr;
	}
}