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

SIN_OBJS = SeqInComp.o SeqIn.o
SOUT_OBJS = SeqOutComp.o SeqOut.o

LINK_LIBS = -L$(TOP_DIR)/lib/rtm -lRTM -L$(TOP_DIR)/lib/orb -lRtORB -luuid

TARGETS = SeqInComp SeqOutComp

all: $(TARGETS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

SeqInComp: $(SIN_OBJS)
	$(CC) -o $@ $(SIN_OBJS) $(LINK_LIBS)

SeqOutComp: $(SOUT_OBJS)
	$(CC) -o $@ $(SOUT_OBJS) $(LINK_LIBS)

clean:
	rm *.o $(TARGETS)
