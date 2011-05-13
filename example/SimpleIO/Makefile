#
#
#
#

UNAME := $(shell uname -s)

TOP_DIR  = ../..

CFLAGS  = -I$(TOP_DIR)/include -I. 
CFLAGS  += -g

CIN_OBJS = ConsoleInComp.o ConsoleIn.o

LINK_LIBS = -L$(TOP_DIR)/lib/rtm -lRTM -L$(TOP_DIR)/lib/orb -lRtORB -luuid

TARGETS = ConsoleInComp

all: $(TARGETS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

ConsoleInComp: $(CIN_OBJS)
	$(CC) -o $@ $(CIN_OBJS) $(LINK_LIBS)

clean:
	rm *.o $(TARGETS)
