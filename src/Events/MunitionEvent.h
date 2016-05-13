#pragma once
#include "Event.h"

class MunitionEvent : public Event
{
public:
    MunitionEvent();
    ~MunitionEvent();

	unsigned char *data[5];
};