#!/bin/bash

export LD_LIBRARY_PATH=$OPENRTM_C_DIR/lib/orb:$OPENRTM_C_DIR/lib/rtm

#gdb ./MyDataOutComp ./rtc.conf
./MyDataOutComp ./rtc.conf
