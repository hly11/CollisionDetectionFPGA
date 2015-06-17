#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/tim/image_filter/solution1/.autopilot/db/a.g.bc ${1+"$@"}
