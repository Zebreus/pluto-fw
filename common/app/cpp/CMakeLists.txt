include_directories(
    /home/lennart/Documents/pluto-fw/target
    /home/lennart/Documents/pluto-fw/target/hal
    /home/lennart/Documents/pluto-fw
    )

set(cppapp_source_files
  entrypoint.cpp
  entrypoint.h
framework/components/timeDisplay.cpp
framework/components/effectTester.cpp
framework/components/buttonTester.cpp
framework/createComponent.cpp
framework/hooks/useTime.cpp
framework/hooks/useEffect.cpp
framework/hooks/useButton.cpp
framework/hooks/useState.cpp
framework/hooks/useGlobalState.cpp
framework/hooks/useUnmountAction.cpp
framework/queue.cpp
framework/loop.cpp
framework/demos/root.cpp
framework/eventQueue.cpp
framework/state.cpp
framework/event.cpp
)

msp430_add_library(cppapp ${cppapp_source_files})