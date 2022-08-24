module;

#include <variant>

export module fw.event;

import fw.createComponent;

// enum EventType {
//     AlarmDown,
//     AlarmUp,
//     LightDown,
//     LightUp,
//     ModeDown,
//     ModeUp,
//     Tick,
//     AuxTimer
// };

export class ModeDownEvent
{
};
export class ModeUpEvent
{
};
export class LightDownEvent
{
};
export class LightUpEvent
{
};
export class AlarmDownEvent
{
};
export class AlarmUpEvent
{
};
export class TickEvent
{
};
export class AuxTimerEvent
{
};
export class StateEvent
{
public:
    StateEvent(ComponentData *component);
    ComponentData *component;
};

export typedef std::variant<ModeDownEvent, ModeUpEvent, LightDownEvent, LightUpEvent, AlarmDownEvent, AlarmUpEvent, TickEvent, AuxTimerEvent, StateEvent> Event;

StateEvent::StateEvent(ComponentData *component) : component(component) {}