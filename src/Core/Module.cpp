#include "Module.h"

Module::Module()
{
}


Module::~Module()
{
}

void Module::pauseEventHandler()
{
	evtHandler->acceptEvents = false;
	evtHandler->emitEvents = false;
}

void Module::startEventHandler()
{
	evtHandler->acceptEvents = true;
	evtHandler->emitEvents = true;
}
