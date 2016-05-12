#pragma once
#include "Event.h"
#include "EventHandler.h"

#define NETWORK_QUEUE_TYPES 4

class Module
{
public:
	Module();
    ~Module();

	void run();

	// takes an Event of type inputEvent and outputs one of type outputEvent
    virtual Event *processEvent(Event *evt) = 0;

protected:
	EventHandler* evtHandler;

	Event::eventType  inputEvent;
	Event::eventType outputEvent;

	void Initialize(std::string inHost,  std::string outHost,
					std::string inQueue, std::string outQueue);

	const std::string networkQueues[NETWORK_QUEUE_TYPES]
	{
		"INPUT_to_ApiModule",
		"ApiModule_to_MunitionModule",
		"MunitionModule_to_PhysicsModule",
		"PhysicsModule_to_OUTPUT"
	};
};

