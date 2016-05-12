#pragma once
#include "Module.h"

class MunitionModule : public Module
{
public:
    MunitionModule();
	MunitionModule(std::string inHost, std::string outHost);
    ~MunitionModule();

	Event *processEvent(Event *evt);
};

