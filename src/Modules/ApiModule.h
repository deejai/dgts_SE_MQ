#pragma once
#include "Module.h"

class ApiModule : public Module
{
public:
	ApiModule();
	~ApiModule();

	Event *processEvent(Event *evt);
};