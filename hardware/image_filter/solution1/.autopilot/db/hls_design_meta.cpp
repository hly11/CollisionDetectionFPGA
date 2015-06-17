#include "hls_design_meta.h"
const Port_Property HLS_Design_Meta::port_props[]={
	Port_Property("s_axi_control_bus_AWVALID", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_AWREADY", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_bus_AWADDR", 6, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_WVALID", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_WREADY", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_bus_WDATA", 32, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_WSTRB", 4, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_ARVALID", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_ARREADY", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_bus_ARADDR", 6, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_RVALID", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_bus_RREADY", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_RDATA", 32, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_bus_RRESP", 2, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_bus_BVALID", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_bus_BREADY", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_bus_BRESP", 2, hls_out, -1, "", "", 1),
	Port_Property("ap_clk", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_rst_n", 1, hls_in, -1, "", "", 1),
	Port_Property("interrupt", 1, hls_out, -1, "", "", 1),
	Port_Property("input_stream_TDATA", 32, hls_in, 0, "axis", "in_data", 1),
	Port_Property("input_stream_TKEEP", 4, hls_in, 1, "axis", "in_data", 1),
	Port_Property("input_stream_TSTRB", 4, hls_in, 2, "axis", "in_data", 1),
	Port_Property("input_stream_TUSER", 1, hls_in, 3, "axis", "in_data", 1),
	Port_Property("input_stream_TLAST", 1, hls_in, 4, "axis", "in_data", 1),
	Port_Property("input_stream_TID", 1, hls_in, 5, "axis", "in_data", 1),
	Port_Property("input_stream_TDEST", 1, hls_in, 6, "axis", "in_data", 1),
	Port_Property("input2_TDATA", 32, hls_in, 7, "axis", "in_data", 1),
	Port_Property("input2_TKEEP", 4, hls_in, 8, "axis", "in_data", 1),
	Port_Property("input2_TSTRB", 4, hls_in, 9, "axis", "in_data", 1),
	Port_Property("input2_TUSER", 1, hls_in, 10, "axis", "in_data", 1),
	Port_Property("input2_TLAST", 1, hls_in, 11, "axis", "in_data", 1),
	Port_Property("input2_TID", 1, hls_in, 12, "axis", "in_data", 1),
	Port_Property("input2_TDEST", 1, hls_in, 13, "axis", "in_data", 1),
	Port_Property("input_stream_TVALID", 1, hls_in, 6, "axis", "in_vld", 1),
	Port_Property("input_stream_TREADY", 1, hls_out, 6, "axis", "in_acc", 1),
	Port_Property("input2_TVALID", 1, hls_in, 13, "axis", "in_vld", 1),
	Port_Property("input2_TREADY", 1, hls_out, 13, "axis", "in_acc", 1),
};
const char* HLS_Design_Meta::dut_name = "image_filter";
