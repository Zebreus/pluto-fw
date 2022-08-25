module;
#include <concepts>
#include <vector>
#include <functional>

export module fw.useUnmountAction;

import fw.createComponent;
import fw.eventQueue;
import fw.event;

export void
useUnmountAction(auto function)
{
    void *data = (void *)current->getHookData();
    if (!data)
    {
        current->setHookData((void *)5, function);
    }

    return;
}