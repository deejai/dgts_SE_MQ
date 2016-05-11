#pragma once
#include "Event.h"
#include "EventHandler.h"

class Module
{
public:
	Module();
    ~Module();

	void pauseEventHandler();
	void startEventHandler();

	// takes an Event of type inputEvent and outputs one of type outputEvent
    virtual Event *processEvent(Event *evt) = 0;

protected:
	EventHandler* evtHandler;

	Event::eventType  inputEvent;
	Event::eventType outputEvent;

	void Initialize(std::string inHost, std::string outHost);

	const std::string queueA = "INPUT_to_ApiModule";
	const std::string queueB = "ApiModule_to_munitionModule";
	const std::string queueC = "munitionModule_to_OUTPUT";

};

