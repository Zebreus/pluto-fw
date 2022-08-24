module;

export module fw.queue;
import fw.event;

export class EventQueue
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