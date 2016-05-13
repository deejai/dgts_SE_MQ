#pragma once
#include <time.h>
#include <iostream>
#include <mutex>

class Event
{
public:
    Event();
    ~Event();

    // eventType::NUM_TYPES gives the number of different Event types
    enum eventType  /*   .   .   .   .   .   */  {  COLLISION , MUNITION , PHYSICS , INSTRUCTION , NUM_TYPES  };
	const std::string eventTypeStrings[NUM_TYPES]{ "COLLISION","MUNITION","PHYSICS","INSTRUCTION" };

    time_t getTimeStamp();
    time_t updateTimeStamp(); // Returns modified timestamp

    bool isInteractiveWith(Event::eventType type);

	eventType getEventID();
	std::string getDescription();

	static Event *stringToEvent(std::string);
	static std::mutex m_mutex;

private:
    time_t timestamp = time(NULL);

protected:
    Event::eventType eventID;
    bool interactions[Event::eventType::NUM_TYPES];
	std::string description;
};