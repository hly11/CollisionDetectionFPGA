set moduleName image_filter_AXIvideo2Mat_32_480_640_5_1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set C_modelName {image_filter_AXIvideo2Mat<32, 480, 640, 5>.1}
set C_modelType { void 0 }
set C_modelArgList { 
	{ AXI_video_strm_V_data_V int 32 regular {axi_s 0 volatile  { input2 data } }  }
	{ AXI_video_strm_V_keep_V int 4 regular {axi_s 0 volatile  { input2 keep } }  }
	{ AXI_video_strm_V_strb_V int 4 regular {axi_s 0 volatile  { input2 strb } }  }
	{ AXI_video_strm_V_user_V int 1 regular {axi_s 0 volatile  { input2 user } }  }
	{ AXI_video_strm_V_last_V int 1 regular {axi_s 0 volatile  { input2 last } }  }
	{ AXI_video_strm_V_id_V int 1 regular {axi_s 0 volatile  { input2 id } }  }
	{ AXI_video_strm_V_dest_V int 1 regular {axi_s 0 volatile  { input2 dest } }  }
	{ img_rows_V_read int 12 regular  }
	{ img_cols_V_read int 12 regular  }
	{ img_data_stream_V float 32 regular {fifo 1 volatile }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "AXI_video_strm_V_data_V", "interface" : "axis", "bitwidth" : 32} , 
 	{ "Name" : "AXI_video_strm_V_keep_V", "interface" : "axis", "bitwidth" : 4} , 
 	{ "Name" : "AXI_video_strm_V_strb_V", "interface" : "axis", "bitwidth" : 4} , 
 	{ "Name" : "AXI_video_strm_V_user_V", "interface" : "axis", "bitwidth" : 1} , 
 	{ "Name" : "AXI_video_strm_V_last_V", "interface" : "axis", "bitwidth" : 1} , 
 	{ "Name" : "AXI_video_strm_V_id_V", "interface" : "axis", "bitwidth" : 1} , 
 	{ "Name" : "AXI_video_strm_V_dest_V", "interface" : "axis", "bitwidth" : 1} , 
 	{ "Name" : "img_rows_V_read", "interface" : "wire", "bitwidth" : 12} , 
 	{ "Name" : "img_cols_V_read", "interface" : "wire", "bitwidth" : 12} , 
 	{ "Name" : "img_data_stream_V", "interface" : "fifo", "bitwidth" : 32} ]}
# RTL Port declarations: 
set portNum 21
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_continue sc_in sc_logic 1 continue -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ input2_TDATA sc_in sc_lv 32 signal 0 } 
	{ input2_TVALID sc_in sc_logic 1 invld 0 } 
	{ input2_TREADY sc_out sc_logic 1 inacc 6 } 
	{ input2_TKEEP sc_in sc_lv 4 signal 1 } 
	{ input2_TSTRB sc_in sc_lv 4 signal 2 } 
	{ input2_TUSER sc_in sc_lv 1 signal 3 } 
	{ input2_TLAST sc_in sc_lv 1 signal 4 } 
	{ input2_TID sc_in sc_lv 1 signal 5 } 
	{ input2_TDEST sc_in sc_lv 1 signal 6 } 
	{ img_rows_V_read sc_in sc_lv 12 signal 7 } 
	{ img_cols_V_read sc_in sc_lv 12 signal 8 } 
	{ img_data_stream_V_din sc_out sc_lv 32 signal 9 } 
	{ img_data_stream_V_full_n sc_in sc_logic 1 signal 9 } 
	{ img_data_stream_V_write sc_out sc_logic 1 signal 9 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_continue", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "continue", "bundle":{"name": "ap_continue", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "input2_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "AXI_video_strm_V_data_V", "role": "default" }} , 
 	{ "name": "input2_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "AXI_video_strm_V_data_V", "role": "default" }} , 
 	{ "name": "input2_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "AXI_video_strm_V_dest_V", "role": "default" }} , 
 	{ "name": "input2_TKEEP", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "AXI_video_strm_V_keep_V", "role": "default" }} , 
 	{ "name": "input2_TSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "AXI_video_strm_V_strb_V", "role": "default" }} , 
 	{ "name": "input2_TUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "AXI_video_strm_V_user_V", "role": "default" }} , 
 	{ "name": "input2_TLAST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "AXI_video_strm_V_last_V", "role": "default" }} , 
 	{ "name": "input2_TID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "AXI_video_strm_V_id_V", "role": "default" }} , 
 	{ "name": "input2_TDEST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "AXI_video_strm_V_dest_V", "role": "default" }} , 
 	{ "name": "img_rows_V_read", "direction": "in", "datatype": "sc_lv", "bitwidth":12, "type": "signal", "bundle":{"name": "img_rows_V_read", "role": "default" }} , 
 	{ "name": "img_cols_V_read", "direction": "in", "datatype": "sc_lv", "bitwidth":12, "type": "signal", "bundle":{"name": "img_cols_V_read", "role": "default" }} , 
 	{ "name": "img_data_stream_V_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "img_data_stream_V", "role": "din" }} , 
 	{ "name": "img_data_stream_V_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "img_data_stream_V", "role": "full_n" }} , 
 	{ "name": "img_data_stream_V_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "img_data_stream_V", "role": "write" }}  ]}
set Spec2ImplPortList { 
	AXI_video_strm_V_data_V { axis {  { input2_TDATA in_data 0 32 }  { input2_TVALID in_vld 0 1 } } }
	AXI_video_strm_V_keep_V { axis {  { input2_TKEEP in_data 0 4 } } }
	AXI_video_strm_V_strb_V { axis {  { input2_TSTRB in_data 0 4 } } }
	AXI_video_strm_V_user_V { axis {  { input2_TUSER in_data 0 1 } } }
	AXI_video_strm_V_last_V { axis {  { input2_TLAST in_data 0 1 } } }
	AXI_video_strm_V_id_V { axis {  { input2_TID in_data 0 1 } } }
	AXI_video_strm_V_dest_V { axis {  { input2_TREADY in_acc 1 1 }  { input2_TDEST in_data 0 1 } } }
	img_rows_V_read { ap_none {  { img_rows_V_read in_data 0 12 } } }
	img_cols_V_read { ap_none {  { img_cols_V_read in_data 0 12 } } }
	img_data_stream_V { ap_fifo {  { img_data_stream_V_din fifo_data 1 32 }  { img_data_stream_V_full_n fifo_status 0 1 }  { img_data_stream_V_write fifo_update 1 1 } } }
}
