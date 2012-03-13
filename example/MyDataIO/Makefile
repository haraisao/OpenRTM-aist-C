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

#### MyDataType.idl ####
IDL_DIR = ./idl
MYDATATYPE_OBJS = $(IDL_DIR)/MyDataType-common.o $(IDL_DIR)/MyDataType-stubs.o $(IDL_DIR)/MyDataType-skels.o
########################

### Add $(MYDATATYPE_OBJS) #####
MYDATA_IN_OBJS = MyDataInComp.o MyDataIn.o $(MYDATATYPE_OBJS)
MYDATA_OUT_OBJS = MyDataOutComp.o MyDataOut.o $(MYDATATYPE_OBJS)

LINK_LIBS = -L$(TOP_DIR)/lib/rtm -lRTM -L$(TOP_DIR)/lib/orb -lRtORB -luuid

TARGETS = MyDataInComp MyDataOutComp

all: $(TARGETS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

MyDataInComp: $(MYDATA_IN_OBJS)
	$(CC) -o $@ $(MYDATA_IN_OBJS) $(LINK_LIBS)

MyDataOutComp: $(MYDATA_OUT_OBJS)
	$(CC) -o $@ $(MYDATA_OUT_OBJS) $(LINK_LIBS)

clean:
	rm *.o $(MYDATATYPE_OBJS) $(TARGETS)
#	rm *.o $(TARGETS)
