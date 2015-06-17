set moduleName image_filter_Loop_1_proc
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set C_modelName {image_filter_Loop_1_proc}
set C_modelType { int 64 }
set C_modelArgList { 
	{ img_resized_data_stream_0_V float 32 regular {fifo 0 volatile }  }
	{ img_0_2_data_stream_0_V float 32 regular {fifo 0 volatile }  }
	{ p_read int 12 regular  }
	{ p_read1 int 12 regular  }
}
set C_modelArgMapList {[ 
	{ "Name" : "img_resized_data_stream_0_V", "interface" : "fifo", "bitwidth" : 32} , 
 	{ "Name" : "img_0_2_data_stream_0_V", "interface" : "fifo", "bitwidth" : 32} , 
 	{ "Name" : "p_read", "interface" : "wire", "bitwidth" : 12} , 
 	{ "Name" : "p_read1", "interface" : "wire", "bitwidth" : 12} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 64} ]}
# RTL Port declarations: 
set portNum 16
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_continue sc_in sc_logic 1 continue -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ img_resized_data_stream_0_V_dout sc_in sc_lv 32 signal 0 } 
	{ img_resized_data_stream_0_V_empty_n sc_in sc_logic 1 signal 0 } 
	{ img_resized_data_stream_0_V_read sc_out sc_logic 1 signal 0 } 
	{ img_0_2_data_stream_0_V_dout sc_in sc_lv 32 signal 1 } 
	{ img_0_2_data_stream_0_V_empty_n sc_in sc_logic 1 signal 1 } 
	{ img_0_2_data_stream_0_V_read sc_out sc_logic 1 signal 1 } 
	{ p_read sc_in sc_lv 12 signal 2 } 
	{ p_read1 sc_in sc_lv 12 signal 3 } 
	{ ap_return sc_out sc_lv 64 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_continue", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "continue", "bundle":{"name": "ap_continue", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "img_resized_data_stream_0_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "img_resized_data_stream_0_V", "role": "dout" }} , 
 	{ "name": "img_resized_data_stream_0_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "img_resized_data_stream_0_V", "role": "empty_n" }} , 
 	{ "name": "img_resized_data_stream_0_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "img_resized_data_stream_0_V", "role": "read" }} , 
 	{ "name": "img_0_2_data_stream_0_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "img_0_2_data_stream_0_V", "role": "dout" }} , 
 	{ "name": "img_0_2_data_stream_0_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "img_0_2_data_stream_0_V", "role": "empty_n" }} , 
 	{ "name": "img_0_2_data_stream_0_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "img_0_2_data_stream_0_V", "role": "read" }} , 
 	{ "name": "p_read", "direction": "in", "datatype": "sc_lv", "bitwidth":12, "type": "signal", "bundle":{"name": "p_read", "role": "default" }} , 
 	{ "name": "p_read1", "direction": "in", "datatype": "sc_lv", "bitwidth":12, "type": "signal", "bundle":{"name": "p_read1", "role": "default" }} , 
 	{ "name": "ap_return", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "ap_return", "role": "default" }}  ]}
set Spec2ImplPortList { 
	img_resized_data_stream_0_V { ap_fifo {  { img_resized_data_stream_0_V_dout fifo_data 0 32 }  { img_resized_data_stream_0_V_empty_n fifo_status 0 1 }  { img_resized_data_stream_0_V_read fifo_update 1 1 } } }
	img_0_2_data_stream_0_V { ap_fifo {  { img_0_2_data_stream_0_V_dout fifo_data 0 32 }  { img_0_2_data_stream_0_V_empty_n fifo_status 0 1 }  { img_0_2_data_stream_0_V_read fifo_update 1 1 } } }
	p_read { ap_none {  { p_read in_data 0 12 } } }
	p_read1 { ap_none {  { p_read1 in_data 0 12 } } }
}
