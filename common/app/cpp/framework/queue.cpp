#include "queue.hpp"

EventQueue::EventQueue(/* args */) : head(0), tail(0)
{
}

EventQueue::~EventQueue()
{
}

void EventQueue::push(const Event &e)
{
    head = ((head + 1) % MAX_EVENTS);
    events[head] = e;
}

Event EventQueue::pop()
{
    tail = ((tail + 1) % MAX_EVENTS);
    return events[tail];
}

bool EventQueue::isEmpty()
{
    return tail == head;
}