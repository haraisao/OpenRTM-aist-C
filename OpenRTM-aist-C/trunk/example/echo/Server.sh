#!/bin/bash
export DYLD_LIBRARY_PATH=../../lib/orb
./Server -ORBInitRef NameService=corbaloc::localhost:2809/NameService
#gdb ./Server
