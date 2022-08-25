export module fw.useTime;

import fw.useGlobalState;

bool prevAlarmPressed = false;
bool prevModePressed = false;
bool prevLightPressed = false;

export enum Button {
    LIGHT,
    ALARM,
    MODE
};

export template <Button button>
bool useTime()
{
    GlobalActionValue<unsigned long> time = useGlobalState<4, unsigned long>(0);
    unsigned long unixTime = time.get();
}