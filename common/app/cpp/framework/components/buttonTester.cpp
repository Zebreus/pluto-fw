module;

#include <vector>
#include <concepts>

export module fw.buttonTester;

import fw.createComponent;
import fw.state;
import fw.useState;
import fw.useButton;

int buttonCounter = 0;
bool prevAlarmPressed = false;
bool prevModePressed = false;
bool prevLightPressed = false;

export std::vector<ComponentData *> buttonTester(State *state, const std::vector<int> &params)
{
    bool alarmPressed = useButton<Button::ALARM>();
    bool modePressed = useButton<Button::MODE>();
    bool lightPressed = useButton<Button::LIGHT>();

    if (prevAlarmPressed == false && alarmPressed == true)
    {
        ++buttonCounter;
    }
    if (prevModePressed == false && modePressed == true)
    {
        ++buttonCounter;
    }
    if (prevLightPressed == false && lightPressed == true)
    {
        ++buttonCounter;
    }

    unsigned long seconds = buttonCounter % 60;
    unsigned long secondsA = seconds % 10;
    unsigned long secondsB = (seconds / 10) % 6;

    state->text[0] = alarmPressed ? '1' : '0';
    state->text[1] = modePressed ? '1' : '0';
    state->text[2] = lightPressed ? '1' : '0';
    state->text[4] = 48 + secondsB;
    state->text[5] = 48 + secondsA;

    prevAlarmPressed = alarmPressed;
    prevModePressed = modePressed;
    prevLightPressed = lightPressed;

    return {};
};