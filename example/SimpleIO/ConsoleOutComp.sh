#!/bin/bash

export LD_LIBRARY_PATH=$OPENRTM_C_DIR/lib/orb:$OPENRTM_C_DIR/lib/rtm

#gdb ./ConsoleOutComp ./rtc.conf
 ./ConsoleOutComp ./rtc.conf
