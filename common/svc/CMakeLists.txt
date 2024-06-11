include_directories(
    /home/lennart/Documents/pluto-fw/target
    /home/lennart/Documents/pluto-fw/target/hal
    /home/lennart/Documents/pluto-fw
    )

set(service_source_files
aux_timer.c
aux_timer.h
beep.c
beep.h
chro.c
chro.h
compass.c
compass.h
init.c
init.h
itoa_tab.c
itoa_tab.h
lcd.c
lcd.h
main.c
main.h
maps.h
melodies.c
melody.c
melody.h
menu.c
menu.h
rtc_adj.c
rtc_adj.h
seconds_since_last_set.c
seconds_since_last_set.h
svc.h
util.c
util.h
maps/ad.c
maps/adg.c
maps/dig8.c
maps/dig9.c
maps/normal.c
)

msp430_add_library(service ${service_source_files})
target_link_libraries(service hal)