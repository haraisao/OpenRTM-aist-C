#
#
#
#

UNAME := $(shell uname -s)
RTORB_DIR  = $(HOME)/src/RtORB-1.0/trunk

CFLAGS  = -I$(RTORB_DIR)/include -I. -I../include

IDL_COMP  = $(RTORB_DIR)/bin/rtorb-idl
IDL_FLAGS = -DORBIT2_IDL -I. -Iidl --nocpp-defs
#IDL_FLAGS += --skeleton-impl

IDL_SOURCES = OpenRTM-aist.idl 

IDL_SKELIMPL = OpenRTM-aist-skelimpl.c

IDL_H = $(IDL_SOURCES:.idl=.h)
IDL_DECLS_H = $(IDL_SOURCES:.idl=-decls.h)
IDL_COMMON_C = $(IDL_SOURCES:.idl=-common.c)
IDL_STUB_C = $(IDL_SOURCES:.idl=-stubs.c)
IDL_STKEL_C = $(IDL_SOURCES:.idl=skels.c)

ALL_SRC = \
        $(IDL_H)   \
        $(IDL_DECLS_H)   \
        $(IDL_COMMON_C)   \
        $(IDL_STUBS_C)   \
        $(IDL_SKELS_C)   \
        $(IDL_SKELIMPL)

LIBRTM = libRTM.so

LIBOBJS = OpenRTM-aist-common.o
LIBOBJS += OpenRTM-aist-skels.o
LIBOBJS += OpenRTM-aist-stubs.o
LIBOBJS += OpenRTM-aist-skelimpl.o
LIBOBJS += Manager.o

LINK_LIBS = -L$(RTORB_DIR)/lib -lRtORB

all:
	$(MAKE) idl_compile
	$(MAKE) $(LIBRTM) 

idl_compile: $(IDL_SOURCES)
	$(IDL_COMP) $(IDL_FLAGS) $(IDL_SOURCES)

skelImpl: 
	$(IDL_COMP) $(IDL_FLAGS) --skeleton-impl $(IDL_SOURCES)

$(LIBRTM): $(LIBOBJS)
	$(CC) -shared -o $@ $(LIBOBJS) $(LINK_LIBS)


clean:
	rm *.o $(IDL_H) $(IDL_DECLS_H) $(IDL_COMMON_C) $(IDL_STUB_C) $(IDL_SKEL_C) $(LIBRTM)
