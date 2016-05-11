#include "Module.h"

Module::Module()
{
}

Module::~Module()
{
}

void Module::Initialize(std::string inHost, std::string outHost)
{
	evtHandler = new EventHandler(inHost, outHost, "", "");
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
