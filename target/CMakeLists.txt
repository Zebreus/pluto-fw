include_directories(
    /nix/store/sw5xd8c9jiaby950q93nl20sybz5bbar-msp430-gcc-support-files-1.207/include
    .
    ./hal
    ../common/svc
    ../common/app/cpp
    /home/lennart/Documents/pluto-fw
    /home/lennart/Documents/pluto-fw/common
    /home/lennart/Documents/pluto-fw/target
    /home/lennart/Documents/pluto-fw/target/hal
    /home/lennart/Documents/pluto-fw/common/app
    /home/lennart/Documents/pluto-fw/common/app/cpp
)

add_subdirectory(hal)

set(target_source_files
main.cpp
# hal/aux_timer.c
# hal/aux_timer.h
# hal/beepled.c
# hal/beepled.h
# hal/button.c
# hal/button.h
# hal/compass.c
# hal/compass.h
# hal/crypto.c
# hal/debug.c
# hal/i2c.c
# hal/i2c.h
# hal/io.c
# hal/io.h
# hal/lcd.c
# hal/lcd.h
# hal/mag3110.c
# hal/mag3110.h
# hal/rtc.c
# hal/rtc.h
# hal/segmap.c
# hal/segmap.h
# hal/wdt.c
# hal/wdt.h
# hal/aes/aes256.c
# hal/aes/aes256.h
# hal/aes/hw_memmap.h
# hal/hal.h
# hal/lcd_segments.h
# ../common/svc/aux_timer.c
# ../common/svc/aux_timer.h
# ../common/svc/beep.c
# ../common/svc/beep.h
# ../common/svc/chro.c
# ../common/svc/chro.h
# ../common/svc/compass.c
# ../common/svc/compass.h
# ../common/svc/init.c
# ../common/svc/init.h
# ../common/svc/itoa_tab.c
# ../common/svc/itoa_tab.h
# ../common/svc/lcd.c
# ../common/svc/lcd.h
# ../common/svc/main.c
# ../common/svc/main.h
# ../common/svc/maps.h
# ../common/svc/melodies.c
# ../common/svc/melody.c
# ../common/svc/melody.h
# ../common/svc/menu.c
# ../common/svc/menu.h
# ../common/svc/rtc_adj.c
# ../common/svc/rtc_adj.h
# ../common/svc/seconds_since_last_set.c
# ../common/svc/seconds_since_last_set.h
# ../common/svc/svc.h
# ../common/svc/util.c
# ../common/svc/util.h
# ../common/svc/maps/ad.c
# ../common/svc/maps/adg.c
# ../common/svc/maps/dig8.c
# ../common/svc/maps/dig9.c
# ../common/svc/maps/normal.c
# ../common/app/cpp/entrypoint.cpp
# ../common/app/cpp/entrypoint.h
# ../common/app/cpp/framework/components/timeDisplay.cpp
# ../common/app/cpp/framework/components/effectTester.cpp
# ../common/app/cpp/framework/components/buttonTester.cpp
# ../common/app/cpp/framework/createComponent.cpp
# ../common/app/cpp/framework/hooks/useTime.cpp
# ../common/app/cpp/framework/hooks/useEffect.cpp
# ../common/app/cpp/framework/hooks/useButton.cpp
# ../common/app/cpp/framework/hooks/useState.cpp
# ../common/app/cpp/framework/hooks/useGlobalState.cpp
# ../common/app/cpp/framework/hooks/useUnmountAction.cpp
# ../common/app/cpp/framework/queue.cpp
# ../common/app/cpp/framework/loop.cpp
# ../common/app/cpp/framework/demos/root.cpp
# ../common/app/cpp/framework/eventQueue.cpp
# ../common/app/cpp/framework/state.cpp
# ../common/app/cpp/framework/event.cpp
)
msp430_add_executable(lx ${target_source_files})

target_link_libraries(lx.elf hal cppapp service)