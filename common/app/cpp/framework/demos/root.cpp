module;

#include <vector>
#include <memory>

export module fw.root;

import fw.createComponent;
import fw.timeDisplay;
import fw.buttonTester;
import fw.effectTester;
import fw.state;

export std::vector<ComponentData *> root(State *state, const std::vector<int> &params)
{
    state->alarm = true;
    auto demoComponent = new ComponentData(timeDisplay, {});
    return {demoComponent};
}