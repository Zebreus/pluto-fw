module;

#include <variant>
#include <vector>

export module fw.loop;
import fw.event;
import fw.useState;
import fw.useGlobalState;
import fw.root;
import fw.state;
import fw.eventQueue;
import fw.createComponent;
import fw.queue;

extern "C"
{
#include "common/svc/svc.h"
#include "hal.h"
#include "lcd_segments.h"
}

// #include "common/app/cpp/framework/hooks/useState.hpp"
// #include "common/app/cpp/framework/hooks/useGlobalState.hpp"
// #include "common/app/cpp/framework/demos/root.hpp"
// #include "common/app/cpp/framework/state.hpp"
// #include "common/app/cpp/framework/eventQueue.hpp"
// #include "common/app/cpp/framework/createComponent.hpp"
// #include "queue.hpp"

export void processEvent(const Event &event);

export void workQueue();

static ComponentData rootComponentV(&root, {});
static ComponentData *rootComponent = &rootComponentV;

export void frameworkInit()
{
    if (rootComponent == nullptr)
    {
        rootComponent = new ComponentData(&root, {});
    }
    if (current == nullptr)
    {
        current = rootComponent;
    }
}

/** Signal a trigger from an external event  */
export void queueEvent(const Event &event)
{
    eventQueue.push(event);
}

/** Process this event and  */
export void processEvent(const Event &event)
{
    auto lastCurrent = current;
    current = nullptr;
    auto alarm = useGlobalState<1, bool>(false);
    auto mode = useGlobalState<2, bool>(false);
    auto light = useGlobalState<3, bool>(false);
    auto time = useGlobalState<4, unsigned long>(0);
    current = lastCurrent;

    if (std::get_if<TickEvent>(&event))
    {
        hal_rtc_timedate_t td;
        hal_rtc_get(&td);
        unsigned long seconds = td.s;
        unsigned long minutes = td.m;
        unsigned long hours = td.h;
        unsigned long newTime = (seconds + (minutes * 60ul) + (hours * 60ul * 60ul)) * 1000ul;
        time.set(newTime);
    }
    if (auto alarmDown = std::get_if<AlarmDownEvent>(&event))
    {
        alarm.set(true);
    }
    if (auto alarmUp = std::get_if<AlarmUpEvent>(&event))
    {
        alarm.set(false);
    }
    if (auto modeDown = std::get_if<ModeDownEvent>(&event))
    {
        mode.set(true);
    }
    if (auto modeUp = std::get_if<ModeUpEvent>(&event))
    {
        mode.set(false);
    }
    if (auto lightDown = std::get_if<LightDownEvent>(&event))
    {
        light.set(true);
    }
    if (auto lightUp = std::get_if<LightUpEvent>(&event))
    {
        light.set(false);
    }
    if (auto stateChanged = std::get_if<StateEvent>(&event))
    {
        // Rerun affected methods
        // noop for debugger
        stateChanged->component->render();
    }
}

State getState(const ComponentData *component)
{
    State state = *(component->state);
    for (const ComponentData *sub : component->lastResult)
    {
        state.layer(getState(sub));
    }
    return state;
}

export void workQueue()
{
    while (!eventQueue.isEmpty())
    {
        processEvent(eventQueue.pop());
    }
    getState(rootComponent).realize();
    // rootComponent->lastResult.front()->state->realize();
};