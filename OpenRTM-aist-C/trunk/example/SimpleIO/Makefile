#
#
#
#

UNAME := $(shell uname -s)

# Need to set environment variable of install directory
TOP_DIR	= $(OPENRTM_C_DIR)

CFLAGS  = -I$(TOP_DIR)/include -I. 
CFLAGS  += -g

ifeq ($(UNAME),Linux)
CFLAGS  += -malign-double
endif

CIN_OBJS = ConsoleInComp.o ConsoleIn.o
COUT_OBJS = ConsoleOutComp.o ConsoleOut.o

LINK_LIBS = -L$(TOP_DIR)/lib/rtm -lRTM -L$(TOP_DIR)/lib/orb -lRtORB -luuid

TARGETS = ConsoleInComp ConsoleOutComp

all: $(TARGETS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

ConsoleInComp: $(CIN_OBJS)
	$(CC) -o $@ $(CIN_OBJS) $(LINK_LIBS)

ConsoleOutComp: $(COUT_OBJS)
	$(CC) -o $@ $(COUT_OBJS) $(LINK_LIBS)

clean:
	rm *.o $(TARGETS)
