#include "Module.h"
#include <iostream>

Module::Module()
{
	std::cout << "Module construction\n";
}

Module::~Module()
{
}

void Module::run()
{
	evtHandler->run(this);
}

void Module::Initialize(std::string inHost, std::string outHost, std::string inQueue, std::string outQueue)
{
	evtHandler = new EventHandler(inHost, outHost, inputEvent, outputEvent, inQueue, outQueue);
}
