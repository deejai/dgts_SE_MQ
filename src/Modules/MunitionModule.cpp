#include "MunitionModule.h"
#include "Event.h"
#include "MunitionEvent.h"
#include "PhysicsEvent.h"

MunitionModule::MunitionModule()
{
	 inputEvent = Event::MUNITION;
	outputEvent = Event::PHYSICS;

	Initialize("localhost", "localhost", Module::networkQueues[1], Module::networkQueues[2]);
}

MunitionModule::MunitionModule(std::string inHost, std::string outHost)
{
	inputEvent = Event::MUNITION;
	outputEvent = Event::PHYSICS;

	Initialize(inHost, outHost, Module::networkQueues[1], Module::networkQueues[2]);
}

MunitionModule::~MunitionModule()
{
}

Event *MunitionModule::processEvent(Event *evt)
{
	if (evt->getEventID("processEvent:munitionMod") == inputEvent) {
		delete evt;

		// Avoid race condition
		Event::m_mutex.lock();
		evt = new PhysicsEvent();
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