#include "Module.h"

Module::Module()
{
}

Module::~Module()
{
}

void Module::Initialize(std::string inHost, std::string outHost)
{
	evtHandler = new EventHandler(inHost, outHost, inputEvent, outputEvent);
}

void Module::run()
{
	evtHandler->run();
}
