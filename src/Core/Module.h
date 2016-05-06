#pragma once
#include "Event.h"
#include "EventHandler.h"

class Module
{
public:
    Module();
    ~Module();

    EventHandler* evtHandler;

    std::string decodeEvent(Event *evt);
    Event *encodeEvent(std::string evtString);
};

