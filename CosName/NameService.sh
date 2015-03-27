#!/bin/bash

#export DYLD_LIBRARY_PATH=$OPENRTM_C_DIR/lib/orb
export LD_LIBRARY_PATH=$OPENRTM_C_DIR/lib/orb

#gdb ./NameService 
./NameService 
