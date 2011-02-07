#
#
#
#

UNAME := $(shell uname -s)
TOP_DIR  = ../..

CFLAGS  = -I$(TOP_DIR)/include -I. -I../include
CFLAGS  += -g
CFLAGS  += -02

IDL_COMP  = $(TOP_DIR)/idl-compiler/rtorb-idl
IDL_FLAGS = -DORBIT2_IDL -I. -Iidl --nocpp-defs
#IDL_FLAGS += --skeleton-impl

IDL_SOURCES = OpenRTM-aist.idl 


IDL_H = $(IDL_SOURCES:.idl=.h)
IDL_DECLS_H = $(IDL_SOURCES:.idl=-decls.h)
IDL_COMMON_C = $(IDL_SOURCES:.idl=-common.c)
IDL_STUB_C = $(IDL_SOURCES:.idl=-stubs.c)
IDL_SKEL_C = $(IDL_SOURCES:.idl=-skels.c)

IDL_SKELIMPL = $(IDL_SOURCES:.idl=-skelimpl.c)

IDL_AUTOGEN_SRC = \
        $(IDL_H)   \
        $(IDL_DECLS_H)   \
        $(IDL_COMMON_C)   \
        $(IDL_STUB_C)   \
        $(IDL_SKEL_C)

LIB_SOURCES = \
        $(IDL_COMMON_C)   \
        $(IDL_STUB_C)   \
        $(IDL_SKEL_C)   \
        $(IDL_SKELIMPL)
LIB_SOURCES += Properties.c
LIB_SOURCES += NVUtil.c
LIB_SOURCES += Utils.c
LIB_SOURCES += Manager.c
LIB_SOURCES += RTObject.c
LIB_SOURCES += PortAdmin.c
LIB_SOURCES += NamingManager.c
LIB_SOURCES += ExecutionContext.c

LIBOBJS = $(LIB_SOURCES:.c=.o)

LINK_LIBS = -L$(TOP_DIR)/lib/orb -lRtORB
LIBRTM = libRTM.so

all:
	$(MAKE) idl_comp
	$(MAKE) $(LIBRTM) 

idl_comp: $(IDL_SOURCES)
	$(IDL_COMP) $(IDL_FLAGS) $(IDL_SOURCES)

skelimpl: 
	$(IDL_COMP) $(IDL_FLAGS) --skeleton-impl $(IDL_SOURCES)

$(LIBRTM): $(LIBOBJS)
	$(CC) -shared -o $@ $(LIBOBJS) $(LINK_LIBS)


clean:
	rm *.o $(IDL_AUTOGEN_SRC) $(LIBRTM)
