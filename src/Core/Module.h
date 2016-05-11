#pragma once
#include "Event.h"
#include "EventHandler.h"

#define NETWORK_QUEUE_TYPES 3

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

private:
	static std::string networkQueues[] =
	{
		"INPUT_to_ApiModule",
		"ApiModule_to_munitionModule",
		"munitionModule_to_OUTPUT"
	};
};

