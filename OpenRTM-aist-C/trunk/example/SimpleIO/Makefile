#
#
#
#

UNAME := $(shell uname -s)
RTORB_DIR  = $(HOME)/src/RtORB-dev/trunk
RTM_DIR  = $(HOME)/src/RtORB-dev/OpenRTM-aist-C/trunk

RTORB_DIR  = $(HOME)/src/RtORB-dev/trunk
RTM_DIR  = $(HOME)/src/RtORB-dev/OpenRTM-aist-C/trunk

CFLAGS  = -I$(RTORB_DIR)/include -I. -I$(RTM_DIR)/include
CFLAGS  += -g

CIN_OBJS = ConsoleInComp.o ConsoleIn.o

LINK_LIBS = -L$(RTM_DIR)/lib -lRTM -L$(RTORB_DIR)/lib -lRtORB

TARGETS = ConsoleInComp

all: $(TARGETS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

ConsoleInComp: $(CIN_OBJS)
	$(CC) -o $@ $(CIN_OBJS) $(LINK_LIBS)

clean:
	rm *.o
