module;

#include <vector>
#include <concepts>

export module fw.timeDisplay;

import fw.createComponent;
import fw.state;
import fw.useState;
import fw.useGlobalState;

export std::vector<ComponentData *> timeDisplay(State *state, const std::vector<int> &params)
{

    GlobalActionValue<unsigned long> time = useGlobalState<4, unsigned long>(0);
    unsigned long unixTime = time.get();

    unsigned long seconds = unixTime / 1000;
    unsigned long secondsA = seconds % 10;
    unsigned long secondsB = (seconds / 10) % 6;
    unsigned long minutes = seconds / 60;
    unsigned long minutesA = minutes % 10;
    unsigned long minutesB = (minutes / 10) % 6;
    unsigned long hours = (minutes / 60) % 24;
    unsigned long hoursA = hours % 10;
    unsigned long hoursB = hours / 10;
    state->text[0] = 48 + hoursB;
    state->text[1] = 48 + hoursA;
    state->text[2] = 48 + minutesB;
    state->text[3] = 48 + minutesA;
    state->text[4] = 48 + secondsB;
    state->text[5] = 48 + secondsA;
    return {};
};