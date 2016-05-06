#pragma once
#include "Event.h"
#include "subscriber.h"
#include "publisher.h"

#define MAX_QUEUED_EVENTS 1000

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();

    struct eventNode {
        Event evt;
        eventNode* next = nullptr;
    };

    void run(std::string host);

    // Communication with RabbitMQ or Module halts while false
    bool acceptEvents = true; // input
    bool   emitEvents = true; // output

    // Get the length of the event queues
    int numUnprocessedEventsQueued();
    int numProcessedEventsQueued();

    const std::string incomingQueue;
    const std::string outgoingQueue;

private:
    // run() does nothing if true
    bool running = false;

    // Consumes Events from RMQ
    Subscriber *subscriber;
    // Publishes Events to RMQ
    Publisher *publisher;

    // Events are stored in a single array queue
    eventNode eventQueue[MAX_QUEUED_EVENTS];
    int start_index = 0;
    int   end_index = 0;
    int numEventsQueued();
    //                   start ▼             end ▼
    // eventQueue [ ][ ][ ][ ][E][E][E][E][E][E][ ][ ][ ]
    //                   index ▲           index ▲


    // Handles the subscriber, writing to the queue, and incrementing the end_index
    static void* acceptor(void* host);

    // Handles the publisher and incrementing the start_index
    static void* emitter(void* host);


    // ----------------------- PERMISSIONS -------------------------------
    //             eventQueue  start_index  end_index
    // acceptor    write only  read only    read/write
    // emitter     read only   read/write   read only
    //
    // The acceptor controls where the emitter may read.


    // Events marked true will be discarded if received
    // (NUM_TYPES is the number of unique event types)
    bool ignoredEvents[Event::eventType::NUM_TYPES];
    // Example: ignoredEvents[Event::eventType::COLLISION] = true;
};