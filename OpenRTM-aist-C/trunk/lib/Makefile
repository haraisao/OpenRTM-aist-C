#
#
#
UNAME := $(shell uname -s)

MAKE_OPT=""

ifneq (,$(findstring CYGWIN, $(UNAME)))
	UNAME = Cygwin
endif


all: orb-lib rtm-lib

orb-lib:
	cd orb && $(MAKE) "DEFINE=$(DEFINE)"

rtm-lib:
	cd rtm && $(MAKE) "DEFINE=$(DEFINE)"


distclean:
	/bin/rm -f *~
	cd idl-compiler && $(MAKE) clean
	cd lib && $(MAKE) allclean
	rm include/RtORB/config_rtorb.h

clean:
	/bin/rm -f *~
	cd idl-compiler && $(MAKE) clean
	cd lib && $(MAKE) allclean
	rm include/RtORB/config_rtorb.h
