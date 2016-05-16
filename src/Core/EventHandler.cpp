#include "EventHandler.h"
#include "Module.h"
#include <iostream>
#include <thread>

EventHandler::EventHandler()
{
	Initialize("localhost",                 "localhost",
		       Event::eventType::NUM_TYPES, Event::eventType::NUM_TYPES,
		       "testQueue",                 "testQueue");
}

EventHandler::EventHandler(     std::string inHost,          std::string outHost,
	                       Event::eventType inEventKey, Event::eventType outEventKey,
	                            std::string inQueue,         std::string outQueue)
{
	Initialize(inHost, outHost, inEventKey, outEventKey, inQueue, outQueue);
}

EventHandler::~EventHandler()
{
	for (int i = 0; i < EVENT_QUEUE_SIZE; i++) {
		delete eventQueue[i];
	}
	delete pub;
	delete sub;
}

void EventHandler::run(Module *myModule)
{
    std::thread acceptorThread(&EventHandler::acceptor, this, myModule);
    std::thread  emitterThread(&EventHandler::emitter, this);

	acceptorThread.join();
	emitterThread.join();

	std::cout << "endrun\n";
}

void EventHandler::Initialize(     std::string inHost,          std::string outHost,
							  Event::eventType inEventKey, Event::eventType outEventKey,
								   std::string inQueue,         std::string outQueue)
{
	// No events ignored by default
	for (int i = 0; i < Event::eventType::NUM_TYPES; i++)
	{
		ignoredEvents[i] = false;
	}
	std::cout << "sub params: " << inHost << ", " << inQueue << ", " << inEventKey << "\n";
	sub = new Subscriber(inHost, inEventKey, inQueue);
	std::cout << "pub params: " << outHost << ", " << outQueue << ", " << outEventKey << "\n";
	pub = new Publisher(outHost, outEventKey, outQueue);
}

void EventHandler::acceptor(Module *myModule)
{
	Event *evt;

	while (acceptorEnabled)
	{
		std::cout << "(acceptor) numEventsQueued: " << numEventsQueued << "\n";
		std::cin.ignore();

		if (numEventsQueued < EVENT_QUEUE_SIZE - 2)
		{
			//If eventQueue has room, try to get an Event from the MQ
			// getNextEvent allocates space for an Event, but emitter deallocates it
			if ( (evt = sub->getNextEvent()) != nullptr )
			{
				// If there's an Event, grab it and queue it

				// TODO: Discard malformed/irrelevant events
				// TODO: Try-Catch to avoid incrementing end_index in case of enqueue failure
				eventQueue[end_index] = myModule->processEvent(evt);

				end_index++;
				numEventsQueued++;

				if (end_index == EVENT_QUEUE_SIZE) {
					end_index = 0;
				}
				else if (end_index > EVENT_QUEUE_SIZE) {
					// If end_index > EVENT_QUEUE_SIZE, terminate program with error
					std::cout << "END_INDEX > EVENT_QUEUE_SIZE. EXITING.\n";
					exit(-1);
				}

			}
			else {
				std::cout << "\nsub->getNextEvent() returned a nullptr...\n";
				std::cin.ignore();
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
			if (eventQueue[start_index] == nullptr) {
				std::cout << "Empty event in start_index. Visualizing queue. Press Enter to continue\n";
				visualizeQueue();
				std::cin.ignore();
			}
			else {
				pub->publishEvent(eventQueue[start_index]);

				// If successful, do all this
				delete eventQueue[start_index];
				start_index++;
				numEventsQueued--;
			}

			std::cout << "(emitter ) numEventsQueued: " << numEventsQueued << "\n";
		}
	}
}

void EventHandler::visualizeQueue()
{
	bool disjointed = start_index > end_index;

	for (int i = 0; i < EVENT_QUEUE_SIZE; i++) {
		if (i == start_index) {
			std::cout << ((start_index == end_index) ? "X" : "S");
		}
		else if (i == end_index ){
			std::cout << "e";
		}
		else if (disjointed){
			std::cout << ((i<start_index || i>end_index) ? "E" : "-");
		}
		else {
			std::cout << ((i<start_index || i>end_index) ? "-" : "E");
		}
	}

	std::cout << "\n";
}