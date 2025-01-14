SRC += ../common/svc/lcd.c \
       ../common/svc/main.c \
       ../common/svc/menu.c \
       ../common/svc/util.c \
       ../common/svc/aux_timer.c \
       ../common/svc/beep.c \
       ../common/svc/melody.c \
       ../common/svc/chro.c \
       ../common/svc/compass.c \
       ../common/svc/init.c \
       ../common/svc/otp.c \
       ../common/svc/seconds_since_last_set.c \
       ../common/svc/rtc_adj.c \

include ../common/svc/otp/sources.mk

MAPS = ../common/svc/maps/normal.map ../common/svc/maps/ad.map ../common/svc/maps/adg.map ../common/svc/maps/dig8.map ../common/svc/maps/dig9.map
MAPS_C = $(MAPS:.map=.c)
MAPS_HEADER = ../common/svc/maps.h

../common/svc/lcd.c: $(MAPS_HEADER)

SRC += $(MAPS_C)

GEN_MAP = ../common/svc/gen_map.py
GEN_ITOA_TAB = ../common/svc/gen_itoa_tab.py
ITOA_TAB_C = ../common/svc/itoa_tab.c
GEN_MAP_H = ../common/svc/gen_map_header.py

$(MAPS_C): %.c: %.map $(GEN_MAP)
	$(GEN_MAP) $< > $@

$(MAPS_HEADER) : $(MAPS) $(GEN_MAP_H)
	$(GEN_MAP_H) $(filter %.map,$^) > $@

$(ITOA_TAB_C): $(GEN_ITOA_TAB)
	$(GEN_ITOA_TAB) > $@

SRC += $(ITOA_TAB_C)

MELODIES_C =  ../common/svc/melodies.c
MELODIES_RTTTL = ../common/svc/melodies.rtttl
GEN_MELODIES = ../common/svc/gen_melodies.py

SRC += $(MELODIES_C)

$(MELODIES_C) : $(MELODIES_RTTTL) $(GEN_MELODIES)
	$(GEN_MELODIES) $< 128 > $@
