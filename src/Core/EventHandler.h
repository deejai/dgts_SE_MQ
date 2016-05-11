#pragma once
#include "Event.h"
#include "subscriber.h"
#include "publisher.h"
#include <atomic>

#define EVENT_QUEUE_SIZE 1000

class EventHandler
{
public:
	EventHandler();
	EventHandler(Event::eventType inEventKey, Event::eventType outEventKey);
	EventHandler(std::string inHost, std::string outHost, Event::eventType inEventKey, Event::eventType outEventKey);
	~EventHandler();

	void run();

	// Communication with RabbitMQ or Module halts while false
	bool acceptEvents = false; // input
	bool   emitEvents = false; // output
	
private:
	void Initialize(std::string inputHost, std::string outputHost, Event::eventType inEventKey, Event::eventType outEventKey);

	// if false, acceptor/emitter will do nothing and return
	bool acceptorEnabled = true;
	bool  emitterEnabled = true;

	// Events are stored in a single array queue
	Event *eventQueue[EVENT_QUEUE_SIZE];
	std::atomic_uint64_t start_index = 0;
	std::atomic_uint64_t   end_index = 0;
	std::atomic_uint64_t numEventsQueued = 0;
	//                   start ▼             end ▼
	// eventQueue [ ][ ][ ][ ][E][E][E][E][E][E][ ][ ][ ]
	//                   index ▲           index ▲


	// Handles the subscriber, writing to the queue, and incrementing the end_index
	void acceptor();
	Subscriber *sub;

	// Handles the publisher and incrementing the start_index
	void emitter();
	Publisher *pub;


	// ----------------------- PERMISSIONS -------------------------------
	//             eventQueue  start_index  end_index
	// acceptor    write only  read only    read/write
	// emitter     read only   read/write   read only
	//
	// The acceptor controls where the emitter may read.
	//--------------------------------------------------------------------

	// Events marked true will be discarded if received
	// (NUM_TYPES is the number of unique event types)
	bool ignoredEvents[Event::eventType::NUM_TYPES];
	// Example: ignoredEvents[Event::eventType::COLLISION] = true;


};