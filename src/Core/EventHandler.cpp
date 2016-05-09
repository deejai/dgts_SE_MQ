#include "EventHandler.h"
#include <iostream>
#include <thread>

EventHandler::EventHandler()
{
    // No events ignored by default
    for (int i = 0; i < Event::eventType::NUM_TYPES; i++)
	{
        ignoredEvents[i] = false;
    }


}

EventHandler::~EventHandler()
{
	for (int i = 0; i < EVENT_QUEUE_SIZE; i++) {
		delete eventQueue[i];
	}
}

void EventHandler::run(std::string inputHost, std::string outputHost)
{
    std::thread acceptorThread(&EventHandler::acceptor, this);
    std::thread  emitterThread(&EventHandler::emitter, this);

	acceptorThread.join();
	emitterThread.join();

	std::cout << "endrun\n";
}

int EventHandler::numUnprocessedEventsQueued()
{
    return 0;
}

int EventHandler::numProcessedEventsQueued()
{
    return 0;
}

void EventHandler::acceptor()
{
	Event *evtPtr;

	while (acceptorEnabled)
	{
		if (numEventsQueued < EVENT_QUEUE_SIZE - 2)
		{
			//If eventQueue has room, try to get an Event from the MQ
			// getNextEvent allocates space for an Event, but emitter deallocates it
			if ((evtPtr = sub->getNextEvent()) != nullptr)
			{
				// If there's an Event, grab it and queue it

				// TODO: Discard malformed/irrelevant events
				// TODO: Try-Catch to avoid incrementing end_index in case of enqueue failure
				eventQueue[end_index] = evtPtr;

				if ((++end_index) == EVENT_QUEUE_SIZE) {
					end_index = 0;
				}
				else if (end_index > EVENT_QUEUE_SIZE) {
					// TODO: If end_index > EVENT_QUEUE_SIZE, terminate program with error
				}

				numEventsQueued++;
			}
		}
	}
}

void EventHandler::emitter()
{
	while (emitterEnabled)
	{
		if (numEventsQueued > 0)
		{
			// If there's an Event in the queue, spit it out
			// TODO: Try-Catch stuff
			pub->publishEvent(eventQueue[start_index]);

			// If successful, do all this
			delete eventQueue[start_index];
			start_index++;
			numEventsQueued--;
		}
	}
}
