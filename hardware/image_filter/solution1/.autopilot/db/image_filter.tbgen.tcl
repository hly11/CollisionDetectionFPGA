set moduleName image_filter
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type dataflow
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set C_modelName {image_filter}
set C_modelType { float 32 }
set C_modelArgList { 
	{ bus_input_axis_V_data_V int 32 regular {axi_s 0 volatile  { input_stream data } }  }
	{ bus_input_axis_V_keep_V int 4 regular {axi_s 0 volatile  { input_stream keep } }  }
	{ bus_input_axis_V_strb_V int 4 regular {axi_s 0 volatile  { input_stream strb } }  }
	{ bus_input_axis_V_user_V int 1 regular {axi_s 0 volatile  { input_stream user } }  }
	{ bus_input_axis_V_last_V int 1 regular {axi_s 0 volatile  { input_stream last } }  }
	{ bus_input_axis_V_id_V int 1 regular {axi_s 0 volatile  { input_stream id } }  }
	{ bus_input_axis_V_dest_V int 1 regular {axi_s 0 volatile  { input_stream dest } }  }
	{ bus_input2_axis_V_data_V int 32 regular {axi_s 0 volatile  { input2 data } }  }
	{ bus_input2_axis_V_keep_V int 4 regular {axi_s 0 volatile  { input2 keep } }  }
	{ bus_input2_axis_V_strb_V int 4 regular {axi_s 0 volatile  { input2 strb } }  }
	{ bus_input2_axis_V_user_V int 1 regular {axi_s 0 volatile  { input2 user } }  }
	{ bus_input2_axis_V_last_V int 1 regular {axi_s 0 volatile  { input2 last } }  }
	{ bus_input2_axis_V_id_V int 1 regular {axi_s 0 volatile  { input2 id } }  }
	{ bus_input2_axis_V_dest_V int 1 regular {axi_s 0 volatile  { input2 dest } }  }
	{ rows int 32 regular {axi_slave 0}  }
	{ cols int 32 regular {axi_slave 0}  }
	{ rows2 int 32 regular {axi_slave 0}  }
	{ cols2 int 32 regular {axi_slave 0}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "bus_input_axis_V_data_V", "interface" : "axis", "bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "input_stream.V.data.V","cData": "uint32","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input_axis_V_keep_V", "interface" : "axis", "bitwidth" : 4,"bitSlice":[{"low":0,"up":3,"cElement": [{"cName": "input_stream.V.keep.V","cData": "uint4","bit_use": { "low": 0,"up": 3},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input_axis_V_strb_V", "interface" : "axis", "bitwidth" : 4,"bitSlice":[{"low":0,"up":3,"cElement": [{"cName": "input_stream.V.strb.V","cData": "uint4","bit_use": { "low": 0,"up": 3},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input_axis_V_user_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input_stream.V.user.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input_axis_V_last_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input_stream.V.last.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input_axis_V_id_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input_stream.V.id.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input_axis_V_dest_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input_stream.V.dest.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input2_axis_V_data_V", "interface" : "axis", "bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "input2.V.data.V","cData": "uint32","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input2_axis_V_keep_V", "interface" : "axis", "bitwidth" : 4,"bitSlice":[{"low":0,"up":3,"cElement": [{"cName": "input2.V.keep.V","cData": "uint4","bit_use": { "low": 0,"up": 3},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input2_axis_V_strb_V", "interface" : "axis", "bitwidth" : 4,"bitSlice":[{"low":0,"up":3,"cElement": [{"cName": "input2.V.strb.V","cData": "uint4","bit_use": { "low": 0,"up": 3},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input2_axis_V_user_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input2.V.user.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input2_axis_V_last_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input2.V.last.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input2_axis_V_id_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input2.V.id.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "bus_input2_axis_V_dest_V", "interface" : "axis", "bitwidth" : 1,"bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "input2.V.dest.V","cData": "uint1","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "rows", "interface" : "axi_slave", "bundle":"control_bus","type":"ap_none","bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "rows","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":24}, "offset_end" : {"in":31}} , 
 	{ "Name" : "cols", "interface" : "axi_slave", "bundle":"control_bus","type":"ap_none","bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "cols","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":32}, "offset_end" : {"in":39}} , 
 	{ "Name" : "rows2", "interface" : "axi_slave", "bundle":"control_bus","type":"ap_none","bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "rows2","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":40}, "offset_end" : {"in":47}} , 
 	{ "Name" : "cols2", "interface" : "axi_slave", "bundle":"control_bus","type":"ap_none","bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "cols2","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":48}, "offset_end" : {"in":55}} , 
 	{ "Name" : "ap_return", "interface" : "axi_slave", "bundle":"control_bus","type":"ap_none","bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "return","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 1,"step" : 0}]}]}], "offset" : {"out":16}} ]}
# RTL Port declarations: 
set portNum 38
set portList { 
	{ s_axi_control_bus_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_bus_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_bus_AWADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_bus_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_bus_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_bus_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_bus_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_bus_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_bus_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_bus_ARADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_bus_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_bus_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_bus_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_bus_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_bus_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_bus_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_bus_BRESP sc_out sc_lv 2 signal -1 } 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ interrupt sc_out sc_logic 1 signal -1 } 
	{ input_stream_TDATA sc_in sc_lv 32 signal 0 } 
	{ input_stream_TKEEP sc_in sc_lv 4 signal 1 } 
	{ input_stream_TSTRB sc_in sc_lv 4 signal 2 } 
	{ input_stream_TUSER sc_in sc_lv 1 signal 3 } 
	{ input_stream_TLAST sc_in sc_lv 1 signal 4 } 
	{ input_stream_TID sc_in sc_lv 1 signal 5 } 
	{ input_stream_TDEST sc_in sc_lv 1 signal 6 } 
	{ input2_TDATA sc_in sc_lv 32 signal 7 } 
	{ input2_TKEEP sc_in sc_lv 4 signal 8 } 
	{ input2_TSTRB sc_in sc_lv 4 signal 9 } 
	{ input2_TUSER sc_in sc_lv 1 signal 10 } 
	{ input2_TLAST sc_in sc_lv 1 signal 11 } 
	{ input2_TID sc_in sc_lv 1 signal 12 } 
	{ input2_TDEST sc_in sc_lv 1 signal 13 } 
	{ input_stream_TVALID sc_in sc_logic 1 invld 6 } 
	{ input_stream_TREADY sc_out sc_logic 1 inacc 6 } 
	{ input2_TVALID sc_in sc_logic 1 invld 13 } 
	{ input2_TREADY sc_out sc_logic 1 inacc 13 } 
}
set NewPortList {[ 
	{ "name": "s_axi_control_bus_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control_bus", "role": "AWADDR" },"address":[{"name":"image_filter","role":"start","value":"0","valid_bit":"0"},{"name":"image_filter","role":"continue","value":"0","valid_bit":"4"},{"name":"image_filter","role":"auto_start","value":"0","valid_bit":"7"},{"name":"rows","role":"data","value":"24"},{"name":"cols","role":"data","value":"32"},{"name":"rows2","role":"data","value":"40"},{"name":"cols2","role":"data","value":"48"}] },
	{ "name": "s_axi_control_bus_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "AWVALID" } },
	{ "name": "s_axi_control_bus_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "AWREADY" } },
	{ "name": "s_axi_control_bus_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "WVALID" } },
	{ "name": "s_axi_control_bus_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "WREADY" } },
	{ "name": "s_axi_control_bus_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control_bus", "role": "WDATA" } },
	{ "name": "s_axi_control_bus_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control_bus", "role": "WSTRB" } },
	{ "name": "s_axi_control_bus_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control_bus", "role": "ARADDR" },"address":[{"name":"image_filter","role":"start","value":"0","valid_bit":"0"},{"name":"image_filter","role":"done","value":"0","valid_bit":"1"},{"name":"image_filter","role":"idle","value":"0","valid_bit":"2"},{"name":"image_filter","role":"ready","value":"0","valid_bit":"3"},{"name":"image_filter","role":"auto_start","value":"0","valid_bit":"7"},{"name":"return","role":"data","value":"16"}] },
	{ "name": "s_axi_control_bus_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "ARVALID" } },
	{ "name": "s_axi_control_bus_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "ARREADY" } },
	{ "name": "s_axi_control_bus_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "RVALID" } },
	{ "name": "s_axi_control_bus_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "RREADY" } },
	{ "name": "s_axi_control_bus_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control_bus", "role": "RDATA" } },
	{ "name": "s_axi_control_bus_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control_bus", "role": "RRESP" } },
	{ "name": "s_axi_control_bus_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "BVALID" } },
	{ "name": "s_axi_control_bus_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control_bus", "role": "BREADY" } },
	{ "name": "s_axi_control_bus_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control_bus", "role": "BRESP" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "interrupt", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "interrupt", "role": "default" }} , 
 	{ "name": "input_stream_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "bus_input_axis_V_data_V", "role": "default" }} , 
 	{ "name": "input_stream_TKEEP", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "bus_input_axis_V_keep_V", "role": "default" }} , 
 	{ "name": "input_stream_TSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "bus_input_axis_V_strb_V", "role": "default" }} , 
 	{ "name": "input_stream_TUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input_axis_V_user_V", "role": "default" }} , 
 	{ "name": "input_stream_TLAST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input_axis_V_last_V", "role": "default" }} , 
 	{ "name": "input_stream_TID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input_axis_V_id_V", "role": "default" }} , 
 	{ "name": "input_stream_TDEST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input_axis_V_dest_V", "role": "default" }} , 
 	{ "name": "input2_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "bus_input2_axis_V_data_V", "role": "default" }} , 
 	{ "name": "input2_TKEEP", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "bus_input2_axis_V_keep_V", "role": "default" }} , 
 	{ "name": "input2_TSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "bus_input2_axis_V_strb_V", "role": "default" }} , 
 	{ "name": "input2_TUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input2_axis_V_user_V", "role": "default" }} , 
 	{ "name": "input2_TLAST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input2_axis_V_last_V", "role": "default" }} , 
 	{ "name": "input2_TID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input2_axis_V_id_V", "role": "default" }} , 
 	{ "name": "input2_TDEST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "bus_input2_axis_V_dest_V", "role": "default" }} , 
 	{ "name": "input_stream_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "bus_input_axis_V_dest_V", "role": "default" }} , 
 	{ "name": "input_stream_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "bus_input_axis_V_dest_V", "role": "default" }} , 
 	{ "name": "input2_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "bus_input2_axis_V_dest_V", "role": "default" }} , 
 	{ "name": "input2_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "bus_input2_axis_V_dest_V", "role": "default" }}  ]}
set Spec2ImplPortList { 
	bus_input_axis_V_data_V { axis {  { input_stream_TDATA in_data 0 32 } } }
	bus_input_axis_V_keep_V { axis {  { input_stream_TKEEP in_data 0 4 } } }
	bus_input_axis_V_strb_V { axis {  { input_stream_TSTRB in_data 0 4 } } }
	bus_input_axis_V_user_V { axis {  { input_stream_TUSER in_data 0 1 } } }
	bus_input_axis_V_last_V { axis {  { input_stream_TLAST in_data 0 1 } } }
	bus_input_axis_V_id_V { axis {  { input_stream_TID in_data 0 1 } } }
	bus_input_axis_V_dest_V { axis {  { input_stream_TDEST in_data 0 1 }  { input_stream_TVALID in_vld 0 1 }  { input_stream_TREADY in_acc 1 1 } } }
	bus_input2_axis_V_data_V { axis {  { input2_TDATA in_data 0 32 } } }
	bus_input2_axis_V_keep_V { axis {  { input2_TKEEP in_data 0 4 } } }
	bus_input2_axis_V_strb_V { axis {  { input2_TSTRB in_data 0 4 } } }
	bus_input2_axis_V_user_V { axis {  { input2_TUSER in_data 0 1 } } }
	bus_input2_axis_V_last_V { axis {  { input2_TLAST in_data 0 1 } } }
	bus_input2_axis_V_id_V { axis {  { input2_TID in_data 0 1 } } }
	bus_input2_axis_V_dest_V { axis {  { input2_TDEST in_data 0 1 }  { input2_TVALID in_vld 0 1 }  { input2_TREADY in_acc 1 1 } } }
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
