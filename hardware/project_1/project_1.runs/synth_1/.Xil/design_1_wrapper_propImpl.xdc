set_property SRC_FILE_INFO {cfile:/home/tim/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_3/design_1_processing_system7_0_3.xdc rfile:../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_3/design_1_processing_system7_0_3.xdc id:1 order:EARLY scoped_inst:design_1_i/processing_system7_0/inst} [current_design]
set_property SRC_FILE_INFO {cfile:/home/tim/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0.xdc rfile:../../../project_1.srcs/sources_1/bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0.xdc id:2 order:EARLY scoped_inst:design_1_i/clk_wiz_0/inst} [current_design]
set_property SRC_FILE_INFO {cfile:/home/tim/project_1/project_1.srcs/constrs_1/new/constr.xdc rfile:../../../project_1.srcs/constrs_1/new/constr.xdc id:3} [current_design]
set_property src_info {type:SCOPED_XDC file:1 line:21 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter clk_fpga_0 0.3
set_property src_info {type:SCOPED_XDC file:2 line:56 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter [get_clocks -of_objects [get_ports clk_in1]] 0.1
set_property src_info {type:XDC file:3 line:6 export:INPUT save:INPUT read:READ} [current_design]
set_max_delay -datapath_only -from [get_pins {design_1_i/axi_vdma_1/U0/I_PRMRY_DATAMOVER/GEN_S2MM_FULL.I_S2MM_FULL_WRAPPER/GEN_INCLUDE_REALIGNER.I_S2MM_REALIGNER/GEN_INCLUDE_SCATTER.I_S2MM_SCATTER/sig_btt_cntr_reg[1]/C}] -to [get_pins design_1_i/axi_vdma_1/U0/I_PRMRY_DATAMOVER/GEN_S2MM_FULL.I_S2MM_FULL_WRAPPER/GEN_INCLUDE_REALIGNER.I_S2MM_REALIGNER/GEN_INCLUDE_SCATTER.I_S2MM_SCATTER/sig_btt_eq_0_reg/D] 6.580
