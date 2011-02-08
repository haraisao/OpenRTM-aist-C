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
	cd orb && $(MAKE) allclean
	cd rtm && $(MAKE) clean
	rm ../include/RtORB/config_rtorb.h

clean:
	/bin/rm -f *~
	cd orb && $(MAKE) allclean
	cd rtm && $(MAKE) clean
	rm ../include/RtORB/config_rtorb.h
allclean:
	/bin/rm -f *~
	cd orb && $(MAKE) allclean
	cd rtm && $(MAKE) clean
	rm ../include/RtORB/config_rtorb.h
