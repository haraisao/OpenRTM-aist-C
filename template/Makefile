
UNAME := $(shell uname -s)

# Need to set environment variable of install directory
TOP_DIR	= $(OPENRTM_C_DIR)

CFLAGS  = -I$(TOP_DIR)/include -I. 
CFLAGS  += -g

ifeq ($(UNAME),Linux)
CFLAGS  += -malign-double
endif

# Need to change to user RTC's name.
RTC_OBJS = RtcTempComp.o RtcTemp.o

LINK_LIBS = -L$(TOP_DIR)/lib/rtm -lRTM -L$(TOP_DIR)/lib/orb -lRtORB -luuid

# Need to change to user RTC's name.
TARGETS = RtcTempComp

all: $(TARGETS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

RtcTempComp: $(RTC_OBJS)
	$(CC) -o $@ $(RTC_OBJS) $(LINK_LIBS)

clean:
	rm *.o $(TARGETS)
