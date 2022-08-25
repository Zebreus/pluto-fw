module;

#include <vector>
#include <concepts>
#include <memory>

export module fw.effectTester;

import fw.createComponent;
import fw.state;
import fw.useUnmountAction;
import fw.useEffect;
import fw.useGlobalState;

volatile unsigned int number = 0;

std::vector<ComponentData *> einzelneZahl(State *state, const std::vector<int> &params)
{
    number = number + 1;
    useUnmountAction([](const void *thing)
                     { number = number - 1; });
    auto pos = params[0];
    auto value = params[1];
    state->text[pos] = 48 + number;
    return {};
};

std::vector<ComponentData *> simpleZahl(State *state, const std::vector<int> &params)
{
    auto pos = params[0];
    auto value = params[1];
    state->text[pos] = 48 + value;
    return {};
};

int toast = 0;

export std::vector<ComponentData *> effectTester(State *state, const std::vector<int> &params)
{

    GlobalActionValue<unsigned long> time = useGlobalState<4, unsigned long>(0);

    unsigned long unixTime = time.get();
    toast = (toast + 1) % 2;

    return {new ComponentData(simpleZahl, {toast, 0})};
    auto number = (unixTime / 1000) % 4;
    // return {new ComponentData(einzelneZahl, {4, 0})};
    if (number == 0)
    {
        return {new ComponentData(einzelneZahl, {0, 0})};
    }
    if (number == 1)
    {
        return {new ComponentData(einzelneZahl, {0, 0}), new ComponentData(einzelneZahl, {1, 0})};
    }
    if (number == 2)
    {
        return {new ComponentData(einzelneZahl, {0, 0}), new ComponentData(einzelneZahl, {1, 0}), new ComponentData(einzelneZahl, {2, 0})};
    }
    if (number == 3)
    {
        return {new ComponentData(einzelneZahl, {4, 0})};
    }

    // auto component = new ComponentData(einzelneZahl, {number, number});
    // return {component};
};