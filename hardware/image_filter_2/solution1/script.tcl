############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project image_filter_2
set_top image_filter_fh
add_files top.cpp
add_files top.h
add_files -tb top.cpp
open_solution "solution1"
set_part {xc7z020clg484-1}
create_clock -period 6.5 -name default
source "./image_filter_2/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
