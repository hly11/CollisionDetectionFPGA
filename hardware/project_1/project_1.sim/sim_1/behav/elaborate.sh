#!/bin/sh -f
xv_path="/media/tim/New/Vivado/2015.1"
ExecStep()
{
"$@"
RETVAL=$?
if [ $RETVAL -ne 0 ]
then
exit $RETVAL
fi
}
ExecStep $xv_path/bin/xelab -wto 2c953d459f5040f7bc256919a02497db -m64 --debug typical --relax --mt 8 --include "../../../project_1.srcs/sources_1/ipshared/xilinx.com/axi_infrastructure_v1_1/cf21a66f/hdl/verilog" --include "../../../project_1.srcs/sources_1/ipshared/xilinx.com/axi_vdma_v6_2/02703168/hdl/src/verilog" --include "../../../project_1.srcs/sources_1/ipshared/xilinx.com/processing_system7_bfm_v2_0/e69044ca/hdl" -L xil_defaultlib -L lib_cdc_v1_0 -L lib_pkg_v1_0 -L fifo_generator_v12_0 -L lib_fifo_v1_0 -L blk_mem_gen_v8_2 -L lib_bmg_v1_0 -L lib_srl_fifo_v1_0 -L axi_datamover_v5_1 -L axi_vdma_v6_2 -L proc_sys_reset_v5_0 -L generic_baseblocks_v2_1 -L axi_infrastructure_v1_1 -L axi_register_slice_v2_1 -L axi_data_fifo_v2_1 -L axi_crossbar_v2_1 -L xbip_utils_v3_0 -L axi_utils_v2_0 -L xbip_pipe_v3_0 -L xbip_dsp48_wrapper_v3_0 -L xbip_dsp48_addsub_v3_0 -L xbip_bram18k_v3_0 -L mult_gen_v12_0 -L floating_point_v7_0 -L axi_protocol_converter_v2_1 -L axi_clock_converter_v2_1 -L axi_dwidth_converter_v2_1 -L unisims_ver -L unimacro_ver -L secureip --snapshot design_1_wrapper_behav xil_defaultlib.design_1_wrapper xil_defaultlib.glbl -log elaborate.log
