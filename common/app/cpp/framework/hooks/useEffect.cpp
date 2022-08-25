module;
#include <concepts>
#include <vector>
#include <functional>

export module fw.useEffect;

import fw.createComponent;
import fw.eventQueue;
import fw.event;

export void
useEffect(std::function<std::function<void()>()> function)
{
    // ValueType *data = (ValueType *)current->getHookData();
    // if (!data)
    // {
    //     data = new ValueType(defaultValue);
    //     current->setHookData(data, [](const void *x)
    //                          { static_cast<const ValueType *>(x)->~ValueType(); });
    // }

    void *data = (void *)current->getHookData();
    if (!data)
    {
        std::function<void()> *cleanupFunction = new std::function<void()>(function());
        current->setHookData(cleanupFunction, [](const void *x)
                             {
                             const std::function<void()>* destruct = (static_cast<const std::function<void()> *>(x));
                                (*destruct)();
                             delete destruct; });
    }

    return;
}