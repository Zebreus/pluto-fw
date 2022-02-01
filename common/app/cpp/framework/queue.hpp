#pragma once

#include <queue>
#include "Event.hpp"

class EventQueue
{
private:
    static constexpr int MAX_EVENTS = 16;
    Event events[MAX_EVENTS];
    int head;
    int tail;
    /* data */
public:
    EventQueue();
    ~EventQueue();
    void push(const Event &e);
    Event pop();
    bool isEmpty();
};
