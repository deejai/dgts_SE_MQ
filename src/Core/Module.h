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
};

