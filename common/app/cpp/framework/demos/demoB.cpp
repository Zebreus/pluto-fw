#include "demoB.hpp"

std::vector<ComponentData*> zeroes(State* state, const std::vector<int>& params){
    auto mode = useGlobalState<3,bool>(false);
        state->text[9] = mode ? '1' : '0';


    return {};
}

std::vector<ComponentData*> ones(State* state, const std::vector<int>& params){
    auto mode = useGlobalState<3,bool>(false);
        state->text[8] = mode ? '1' : '0';
     

    return {};
}

std::vector<ComponentData*> showAlarm(State* state, const std::vector<int>& params){
    auto mode = useGlobalState<2,bool>(false);
    int position = params[0];
    state->text[position] = mode ? '1' : '0';

    return {};
}

std::vector<ComponentData*> showTime(State* state, const std::vector<int>& params){
auto time = useGlobalState<4,unsigned long long>(0);
auto unixTime = time;
auto seconds = unixTime/1000;
auto secondsA = seconds%10;
auto secondsB = (seconds/10)%6;
auto minutes = seconds/60;
auto minutesA = minutes%10;
auto minutesB = (minutes/10)%6;
auto hours = (minutes/60)%24;
auto hoursA = hours%10;
auto hoursB = hours/10;
state->text[0] = 48 + hoursB;
state->text[1] = 48 + hoursA;
state->text[2] = 48 + minutesB;
state->text[3] = 48 + minutesA;
state->text[4] = 48 + secondsB;
state->text[5] = 48 + secondsA;
return {};
}

std::vector<ComponentData*> demoB(State* state, const std::vector<int>& params){
    volatile int x = 0;
    auto test = useState<int>(7);
    auto alarm = useGlobalState<1,bool>(false);

    
    const char value = '2' ;
    state->backlight = alarm?true:false;
    // state->beeper = alarm?true:false;

    return { new ComponentData(showTime,{}), new ComponentData(showAlarm, {6}), new ComponentData(showAlarm, {7}) };
}