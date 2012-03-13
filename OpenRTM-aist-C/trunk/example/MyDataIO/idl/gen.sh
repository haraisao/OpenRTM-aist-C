#!/bin/sh

$OPENRTM_C_DIR/bin/rtorb-idl  -DORBIT2_IDL -I. -Iidl --nocpp-defs MyDataType.idl
