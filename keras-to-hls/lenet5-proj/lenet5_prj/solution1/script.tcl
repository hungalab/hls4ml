############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lenet5_prj
set_top lenet5
add_files firmware/lenet5.cpp -cflags "-I/home/hlab/hikari/Repos/hls4ml-sheryl/nnet_utils -std=c++0x"
add_files -tb lenet5_test.cpp -cflags "-I/home/hlab/hikari/Repos/hls4ml-sheryl/nnet_utils -std=c++0x"
add_files -tb ../../../../../../asap2/hikari/vivado_prj_quant_lstm/test_images
add_files -tb firmware/weights
open_solution "solution1"
set_part {xcku095-ffvb2104-1-c}
create_clock -period 10 -name default
#source "./lenet5_prj/solution1/directives.tcl"
csim_design -clean -compiler gcc
csynth_design
cosim_design
export_design -format ip_catalog
