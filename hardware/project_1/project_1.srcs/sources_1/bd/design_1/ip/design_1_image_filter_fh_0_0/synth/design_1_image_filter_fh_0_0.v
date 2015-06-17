// (c) Copyright 1995-2015 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:hls:image_filter_fh:1.0
// IP Revision: 1506031353

(* X_CORE_INFO = "image_filter_fh,Vivado 2015.1" *)
(* CHECK_LICENSE_TYPE = "design_1_image_filter_fh_0_0,image_filter_fh,{}" *)
(* CORE_GENERATION_INFO = "design_1_image_filter_fh_0_0,image_filter_fh,{x_ipProduct=Vivado 2015.1,x_ipVendor=xilinx.com,x_ipLibrary=hls,x_ipName=image_filter_fh,x_ipVersion=1.0,x_ipCoreRevision=1506031353,x_ipLanguage=VERILOG,x_ipSimLanguage=MIXED,C_S_AXI_CONTROL_BUS_ADDR_WIDTH=6,C_S_AXI_CONTROL_BUS_DATA_WIDTH=32}" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module design_1_image_filter_fh_0_0 (
  s_axi_control_bus_AWADDR,
  s_axi_control_bus_AWVALID,
  s_axi_control_bus_AWREADY,
  s_axi_control_bus_WDATA,
  s_axi_control_bus_WSTRB,
  s_axi_control_bus_WVALID,
  s_axi_control_bus_WREADY,
  s_axi_control_bus_BRESP,
  s_axi_control_bus_BVALID,
  s_axi_control_bus_BREADY,
  s_axi_control_bus_ARADDR,
  s_axi_control_bus_ARVALID,
  s_axi_control_bus_ARREADY,
  s_axi_control_bus_RDATA,
  s_axi_control_bus_RRESP,
  s_axi_control_bus_RVALID,
  s_axi_control_bus_RREADY,
  ap_clk,
  ap_rst_n,
  interrupt,
  input_stream_TVALID,
  input_stream_TREADY,
  input_stream_TDATA,
  input_stream_TKEEP,
  input_stream_TSTRB,
  input_stream_TUSER,
  input_stream_TLAST,
  input_stream_TID,
  input_stream_TDEST,
  output_stream_TVALID,
  output_stream_TREADY,
  output_stream_TDATA,
  output_stream_TKEEP,
  output_stream_TSTRB,
  output_stream_TUSER,
  output_stream_TLAST,
  output_stream_TID,
  output_stream_TDEST
);

(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus AWADDR" *)
input wire [5 : 0] s_axi_control_bus_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus AWVALID" *)
input wire s_axi_control_bus_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus AWREADY" *)
output wire s_axi_control_bus_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus WDATA" *)
input wire [31 : 0] s_axi_control_bus_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus WSTRB" *)
input wire [3 : 0] s_axi_control_bus_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus WVALID" *)
input wire s_axi_control_bus_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus WREADY" *)
output wire s_axi_control_bus_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus BRESP" *)
output wire [1 : 0] s_axi_control_bus_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus BVALID" *)
output wire s_axi_control_bus_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus BREADY" *)
input wire s_axi_control_bus_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus ARADDR" *)
input wire [5 : 0] s_axi_control_bus_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus ARVALID" *)
input wire s_axi_control_bus_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus ARREADY" *)
output wire s_axi_control_bus_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus RDATA" *)
output wire [31 : 0] s_axi_control_bus_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus RRESP" *)
output wire [1 : 0] s_axi_control_bus_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus RVALID" *)
output wire s_axi_control_bus_RVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control_bus RREADY" *)
input wire s_axi_control_bus_RREADY;
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *)
input wire ap_clk;
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *)
input wire ap_rst_n;
(* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *)
output wire interrupt;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TVALID" *)
input wire input_stream_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TREADY" *)
output wire input_stream_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TDATA" *)
input wire [31 : 0] input_stream_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TKEEP" *)
input wire [3 : 0] input_stream_TKEEP;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TSTRB" *)
input wire [3 : 0] input_stream_TSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TUSER" *)
input wire [0 : 0] input_stream_TUSER;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TLAST" *)
input wire [0 : 0] input_stream_TLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TID" *)
input wire [0 : 0] input_stream_TID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 input_stream TDEST" *)
input wire [0 : 0] input_stream_TDEST;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TVALID" *)
output wire output_stream_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TREADY" *)
input wire output_stream_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TDATA" *)
output wire [31 : 0] output_stream_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TKEEP" *)
output wire [3 : 0] output_stream_TKEEP;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TSTRB" *)
output wire [3 : 0] output_stream_TSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TUSER" *)
output wire [0 : 0] output_stream_TUSER;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TLAST" *)
output wire [0 : 0] output_stream_TLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TID" *)
output wire [0 : 0] output_stream_TID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 output_stream TDEST" *)
output wire [0 : 0] output_stream_TDEST;

  image_filter_fh #(
    .C_S_AXI_CONTROL_BUS_ADDR_WIDTH(6),
    .C_S_AXI_CONTROL_BUS_DATA_WIDTH(32)
  ) inst (
    .s_axi_control_bus_AWADDR(s_axi_control_bus_AWADDR),
    .s_axi_control_bus_AWVALID(s_axi_control_bus_AWVALID),
    .s_axi_control_bus_AWREADY(s_axi_control_bus_AWREADY),
    .s_axi_control_bus_WDATA(s_axi_control_bus_WDATA),
    .s_axi_control_bus_WSTRB(s_axi_control_bus_WSTRB),
    .s_axi_control_bus_WVALID(s_axi_control_bus_WVALID),
    .s_axi_control_bus_WREADY(s_axi_control_bus_WREADY),
    .s_axi_control_bus_BRESP(s_axi_control_bus_BRESP),
    .s_axi_control_bus_BVALID(s_axi_control_bus_BVALID),
    .s_axi_control_bus_BREADY(s_axi_control_bus_BREADY),
    .s_axi_control_bus_ARADDR(s_axi_control_bus_ARADDR),
    .s_axi_control_bus_ARVALID(s_axi_control_bus_ARVALID),
    .s_axi_control_bus_ARREADY(s_axi_control_bus_ARREADY),
    .s_axi_control_bus_RDATA(s_axi_control_bus_RDATA),
    .s_axi_control_bus_RRESP(s_axi_control_bus_RRESP),
    .s_axi_control_bus_RVALID(s_axi_control_bus_RVALID),
    .s_axi_control_bus_RREADY(s_axi_control_bus_RREADY),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .interrupt(interrupt),
    .input_stream_TVALID(input_stream_TVALID),
    .input_stream_TREADY(input_stream_TREADY),
    .input_stream_TDATA(input_stream_TDATA),
    .input_stream_TKEEP(input_stream_TKEEP),
    .input_stream_TSTRB(input_stream_TSTRB),
    .input_stream_TUSER(input_stream_TUSER),
    .input_stream_TLAST(input_stream_TLAST),
    .input_stream_TID(input_stream_TID),
    .input_stream_TDEST(input_stream_TDEST),
    .output_stream_TVALID(output_stream_TVALID),
    .output_stream_TREADY(output_stream_TREADY),
    .output_stream_TDATA(output_stream_TDATA),
    .output_stream_TKEEP(output_stream_TKEEP),
    .output_stream_TSTRB(output_stream_TSTRB),
    .output_stream_TUSER(output_stream_TUSER),
    .output_stream_TLAST(output_stream_TLAST),
    .output_stream_TID(output_stream_TID),
    .output_stream_TDEST(output_stream_TDEST)
  );
endmodule
