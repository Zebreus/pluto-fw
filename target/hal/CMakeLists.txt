

set(hal_source_files
aux_timer.c
aux_timer.h
beepled.c
beepled.h
button.c
button.h
compass.c
compass.h
crypto.c
debug.c
i2c.c
i2c.h
io.c
io.h
lcd.c
lcd.h
mag3110.c
mag3110.h
rtc.c
rtc.h
segmap.c
segmap.h
wdt.c
wdt.h
aes/aes256.c
aes/aes256.h
aes/hw_memmap.h
hal.h
lcd_segments.h
)

msp430_add_library(hal ${hal_source_files})