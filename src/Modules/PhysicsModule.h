#pragma once
#include "Module.h"

class PhysicsModule : public Module
{
public:
    PhysicsModule();
	PhysicsModule(std::string inHost, std::string outHost);
    ~PhysicsModule();

	Event *processEvent(Event *evt);
};