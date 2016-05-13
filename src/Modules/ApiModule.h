#pragma once
#include "Module.h"

class ApiModule : public Module
{
public:
	ApiModule();
	ApiModule(std::string inHost, std::string outHost);
	~ApiModule();
	
	Event *processEvent(Event *evt);
};