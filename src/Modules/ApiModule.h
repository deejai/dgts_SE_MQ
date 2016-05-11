#pragma once
#include "Module.h"
#include "CollisionEvent.h"
#include "MunitionEvent.h"

class ApiModule : public Module
{
public:
	ApiModule();
	~ApiModule();

	CollisionEvent *processEvent(MunitionEvent *evt);
};