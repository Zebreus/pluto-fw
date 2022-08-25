export module fw.useButton;

import fw.state;
import fw.queue;
import fw.useGlobalState;

export enum Button {
    LIGHT,
    ALARM,
    MODE
};

export template <Button button>
bool useButton()
{
    auto value = useGlobalState<button, bool>(false);
    return value.get();
}