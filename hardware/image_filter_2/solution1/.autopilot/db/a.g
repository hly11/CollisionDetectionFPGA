#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/tim/image_filter_2/solution1/.autopilot/db/a.g.bc ${1+"$@"}
