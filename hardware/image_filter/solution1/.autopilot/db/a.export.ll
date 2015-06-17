; ModuleID = '/home/tim/image_filter/solution1/.autopilot/db/a.o.2.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@p_str1805 = private unnamed_addr constant [12 x i8] c"hls_label_0\00", align 1
@p_str1806 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@p_str1807 = private unnamed_addr constant [12 x i8] c"hls_label_1\00", align 1
@p_str1808 = private unnamed_addr constant [5 x i8] c"axis\00", align 1
@p_str1809 = private unnamed_addr constant [15 x i8] c"bus_input_axis\00", align 1
@p_str1810 = private unnamed_addr constant [16 x i8] c"bus_input2_axis\00", align 1
@p_str1811 = private unnamed_addr constant [10 x i8] c"s_axilite\00", align 1
@p_str1812 = private unnamed_addr constant [12 x i8] c"control_bus\00", align 1
@p_str1819 = private unnamed_addr constant [20 x i8] c"loop_wait_for_start\00", align 1
@p_str1820 = private unnamed_addr constant [12 x i8] c"loop_height\00", align 1
@p_str1821 = private unnamed_addr constant [11 x i8] c"loop_width\00", align 1
@p_str1822 = private unnamed_addr constant [14 x i8] c"loop_channels\00", align 1
@p_str1823 = private unnamed_addr constant [18 x i8] c"loop_wait_for_eol\00", align 1
@p_str1843 = private unnamed_addr constant [12 x i8] c"hls_label_8\00", align 1
@p_str1845 = private unnamed_addr constant [13 x i8] c"hls_label_10\00", align 1
@llvm_global_ctors_0 = appending global [1 x i32] [i32 65535]
@llvm_global_ctors_1 = appending global [1 x void ()*] [void ()* @_GLOBAL__I_a]
@str = internal constant [13 x i8] c"image_filter\00"
@p_str1 = internal constant [71 x i8] c"hls::LineBuffer<2, 641, hls::Scalar<1, float>, 0>::LineBuffer.1.region\00"
@str50 = internal constant [25 x i8] c"img_0_1.data_stream[0].V\00"
@str51 = internal constant [1 x i8] zeroinitializer
@str52 = internal constant [8 x i8] c"ap_fifo\00"
@str53 = internal constant [1 x i8] zeroinitializer
@str54 = internal constant [29 x i8] c"img_resized.data_stream[0].V\00"
@str55 = internal constant [1 x i8] zeroinitializer
@str56 = internal constant [8 x i8] c"ap_fifo\00"
@str57 = internal constant [1 x i8] zeroinitializer
@str58 = internal constant [25 x i8] c"img_0_2.data_stream[0].V\00"
@str59 = internal constant [1 x i8] zeroinitializer
@str60 = internal constant [8 x i8] c"ap_fifo\00"
@str61 = internal constant [1 x i8] zeroinitializer

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @_ssdm_SpecDependence(...) nounwind

define weak void @_ssdm_op_SpecPipeline(...) nounwind {
entry:
  ret void
}

define weak void @_ssdm_op_SpecDataflowPipeline(...) nounwind {
entry:
  ret void
}

define float @image_filter(i32* %bus_input_axis_V_data_V, i4* %bus_input_axis_V_keep_V, i4* %bus_input_axis_V_strb_V, i1* %bus_input_axis_V_user_V, i1* %bus_input_axis_V_last_V, i1* %bus_input_axis_V_id_V, i1* %bus_input_axis_V_dest_V, i32* %bus_input2_axis_V_data_V, i4* %bus_input2_axis_V_keep_V, i4* %bus_input2_axis_V_strb_V, i1* %bus_input2_axis_V_user_V, i1* %bus_input2_axis_V_last_V, i1* %bus_input2_axis_V_id_V, i1* %bus_input2_axis_V_dest_V, i32 %rows, i32 %cols, i32 %rows2, i32 %cols2) {
Mat.exit20:
  call void (...)* @_ssdm_op_SpecDataflowPipeline(i32 -1, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %bus_input_axis_V_data_V), !map !7
  call void (...)* @_ssdm_op_SpecBitsMap(i4* %bus_input_axis_V_keep_V), !map !11
  call void (...)* @_ssdm_op_SpecBitsMap(i4* %bus_input_axis_V_strb_V), !map !15
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input_axis_V_user_V), !map !19
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input_axis_V_last_V), !map !23
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input_axis_V_id_V), !map !27
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input_axis_V_dest_V), !map !31
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %bus_input2_axis_V_data_V), !map !35
  call void (...)* @_ssdm_op_SpecBitsMap(i4* %bus_input2_axis_V_keep_V), !map !39
  call void (...)* @_ssdm_op_SpecBitsMap(i4* %bus_input2_axis_V_strb_V), !map !43
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input2_axis_V_user_V), !map !47
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input2_axis_V_last_V), !map !51
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input2_axis_V_id_V), !map !55
  call void (...)* @_ssdm_op_SpecBitsMap(i1* %bus_input2_axis_V_dest_V), !map !59
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %rows), !map !63
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %cols), !map !69
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %rows2), !map !73
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %cols2), !map !77
  call void (...)* @_ssdm_op_SpecBitsMap(float 0.000000e+00) nounwind, !map !81
  call void (...)* @_ssdm_op_SpecTopModule([13 x i8]* @str) nounwind
  %cols2_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %cols2)
  %rows2_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %rows2)
  %cols_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %cols)
  %rows_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %rows)
  %img_0_1_data_stream_0_V = alloca float, align 4
  %empty = call i32 (...)* @_ssdm_op_SpecChannel([25 x i8]* @str50, i32 1, [1 x i8]* @str51, [1 x i8]* @str51, i32 1, i32 1, float* %img_0_1_data_stream_0_V, float* %img_0_1_data_stream_0_V)
  call void (...)* @_ssdm_op_SpecInterface(float* %img_0_1_data_stream_0_V, [8 x i8]* @str52, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str53, [1 x i8]* @str53, [8 x i8]* @str52)
  %img_resized_data_stream_0_V = alloca float, align 4
  %empty_19 = call i32 (...)* @_ssdm_op_SpecChannel([29 x i8]* @str54, i32 1, [1 x i8]* @str55, [1 x i8]* @str55, i32 1, i32 1, float* %img_resized_data_stream_0_V, float* %img_resized_data_stream_0_V)
  call void (...)* @_ssdm_op_SpecInterface(float* %img_resized_data_stream_0_V, [8 x i8]* @str56, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str57, [1 x i8]* @str57, [8 x i8]* @str56)
  %img_0_2_data_stream_0_V = alloca float, align 4
  %empty_20 = call i32 (...)* @_ssdm_op_SpecChannel([25 x i8]* @str58, i32 1, [1 x i8]* @str59, [1 x i8]* @str59, i32 20000, i32 20000, float* %img_0_2_data_stream_0_V, float* %img_0_2_data_stream_0_V)
  call void (...)* @_ssdm_op_SpecInterface(float* %img_0_2_data_stream_0_V, [8 x i8]* @str60, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str61, [1 x i8]* @str61, [8 x i8]* @str60)
  call void (...)* @_ssdm_op_SpecInterface(i32* %bus_input_axis_V_data_V, i4* %bus_input_axis_V_keep_V, i4* %bus_input_axis_V_strb_V, i1* %bus_input_axis_V_user_V, i1* %bus_input_axis_V_last_V, i1* %bus_input_axis_V_id_V, i1* %bus_input_axis_V_dest_V, [5 x i8]* @p_str1808, i32 0, i32 0, i32 0, i32 0, [15 x i8]* @p_str1809, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %bus_input2_axis_V_data_V, i4* %bus_input2_axis_V_keep_V, i4* %bus_input2_axis_V_strb_V, i1* %bus_input2_axis_V_user_V, i1* %bus_input2_axis_V_last_V, i1* %bus_input2_axis_V_id_V, i1* %bus_input2_axis_V_dest_V, [5 x i8]* @p_str1808, i32 0, i32 0, i32 0, i32 0, [16 x i8]* @p_str1810, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 %rows2, [10 x i8]* @p_str1811, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1812, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 %cols2, [10 x i8]* @p_str1811, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1812, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 %rows, [10 x i8]* @p_str1811, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1812, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 %cols, [10 x i8]* @p_str1811, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1812, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 0, [10 x i8]* @p_str1811, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1812, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806) nounwind
  %call_ret = call fastcc { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } @image_filter_Block_Mat.exit2020_proc(i32 %rows_read, i32 %cols_read, i32 %rows2_read, i32 %cols2_read)
  %img_0_1_rows_V_channel = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 0
  %img_0_1_rows_V_channel1 = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 1
  %img_0_1_cols_V_channel = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 2
  %img_0_1_cols_V_channel1 = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 3
  %img_resized_rows_V_channel = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 4
  %img_resized_rows_V_channel1 = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 5
  %img_resized_cols_V_channel = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 6
  %img_resized_cols_V_channel1 = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 7
  %img_0_2_rows_V_channel = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 8
  %img_0_2_cols_V_channel = extractvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %call_ret, 9
  call fastcc void @"image_filter_AXIvideo2Mat<32, 480, 640, 5>"(i32* %bus_input_axis_V_data_V, i4* %bus_input_axis_V_keep_V, i4* %bus_input_axis_V_strb_V, i1* %bus_input_axis_V_user_V, i1* %bus_input_axis_V_last_V, i1* %bus_input_axis_V_id_V, i1* %bus_input_axis_V_dest_V, i12 %img_0_1_rows_V_channel, i12 %img_0_1_cols_V_channel, float* %img_0_1_data_stream_0_V)
  call fastcc void @"image_filter_AXIvideo2Mat<32, 480, 640, 5>.1"(i32* %bus_input2_axis_V_data_V, i4* %bus_input2_axis_V_keep_V, i4* %bus_input2_axis_V_strb_V, i1* %bus_input2_axis_V_user_V, i1* %bus_input2_axis_V_last_V, i1* %bus_input2_axis_V_id_V, i1* %bus_input2_axis_V_dest_V, i12 %img_0_2_rows_V_channel, i12 %img_0_2_cols_V_channel, float* %img_0_2_data_stream_0_V)
  call fastcc void @image_filter_Resize_Test(i12 %img_0_1_rows_V_channel1, i12 %img_0_1_cols_V_channel1, float* %img_0_1_data_stream_0_V, i12 %img_resized_rows_V_channel, i12 %img_resized_cols_V_channel, float* %img_resized_data_stream_0_V)
  %tmp_loc_channel = call fastcc i64 @image_filter_Loop_1_proc(float* %img_resized_data_stream_0_V, float* %img_0_2_data_stream_0_V, i12 %img_resized_cols_V_channel1, i12 %img_resized_rows_V_channel1)
  %p_0_i_i_loc_channel = call fastcc float @image_filter_Block_.loopexit24.i_proc1(i64 %tmp_loc_channel)
  %res = call fastcc float @image_filter_sqrtf1(float %p_0_i_i_loc_channel)
  ret float %res
}

define weak void @_ssdm_op_SpecInterface(...) nounwind {
entry:
  ret void
}

define weak void @_ssdm_op_SpecLoopName(...) nounwind {
entry:
  ret void
}

define weak void @_ssdm_op_SpecLoopTripCount(...) nounwind {
entry:
  ret void
}

declare i32 @llvm.part.set.i32.i8(i32, i8, i32, i32) nounwind readnone

define weak void @_ssdm_op_SpecProtocol(...) nounwind {
entry:
  ret void
}

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

declare void @_GLOBAL__I_a() nounwind section ".text.startup"

declare float @llvm.sqrt.f32(float) nounwind readonly

define weak i32 @_ssdm_op_SpecRegionBegin(...) {
entry:
  ret i32 0
}

define weak i32 @_ssdm_op_SpecRegionEnd(...) {
entry:
  ret i32 0
}

define weak i16 @_ssdm_op_PartSelect.i16.i32.i32.i32(i32, i32, i32) nounwind readnone {
entry:
  %empty = call i32 @llvm.part.select.i32(i32 %0, i32 %1, i32 %2)
  %empty_21 = trunc i32 %empty to i16
  ret i16 %empty_21
}

define weak i11 @_ssdm_op_PartSelect.i11.i64.i32.i32(i64, i32, i32) nounwind readnone {
entry:
  %empty = call i64 @llvm.part.select.i64(i64 %0, i32 %1, i32 %2)
  %empty_22 = trunc i64 %empty to i11
  ret i11 %empty_22
}

define weak i8 @_ssdm_op_PartSelect.i8.i32.i32.i32(i32, i32, i32) nounwind readnone {
entry:
  %empty = call i32 @llvm.part.select.i32(i32 %0, i32 %1, i32 %2)
  %empty_23 = trunc i32 %empty to i8
  ret i8 %empty_23
}

define weak i53 @_ssdm_op_BitConcatenate.i53.i1.i52(i1, i52) nounwind readnone {
entry:
  %empty = zext i1 %0 to i53
  %empty_24 = zext i52 %1 to i53
  %empty_25 = shl i53 %empty, 52
  %empty_26 = or i53 %empty_25, %empty_24
  ret i53 %empty_26
}

define weak i32 @_ssdm_op_SpecChannel(...) {
entry:
  ret i32 0
}

define internal fastcc void @"image_filter_AXIvideo2Mat<32, 480, 640, 5>"(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V, i12 %img_rows_V_read, i12 %img_cols_V_read, float* %img_data_stream_V) {
.critedge:
  call void (...)* @_ssdm_op_SpecInterface(i1* %AXI_video_strm_V_dest_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_user_V, i4* %AXI_video_strm_V_strb_V, i4* %AXI_video_strm_V_keep_V, i32* %AXI_video_strm_V_data_V, [5 x i8]* @p_str1808, i32 0, i32 0, i32 0, i32 0, [15 x i8]* @p_str1809, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806)
  call void (...)* @_ssdm_op_SpecInterface(float* %img_data_stream_V, [8 x i8]* @str52, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str53, [1 x i8]* @str53, [8 x i8]* @str52)
  %img_cols_V_read_1 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %img_cols_V_read)
  %img_rows_V_read_1 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %img_rows_V_read)
  br label %0

; <label>:0                                       ; preds = %0, %.critedge
  call void (...)* @_ssdm_op_SpecLoopName([20 x i8]* @p_str1819) nounwind
  %tmp = call i32 (...)* @_ssdm_op_SpecRegionBegin([20 x i8]* @p_str1819)
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 0, i32 0, [1 x i8]* @p_str1806) nounwind
  %empty = call { i32, i4, i4, i1, i1, i1, i1 } @_ssdm_op_Read.axis.volatile.i32P.i4P.i4P.i1P.i1P.i1P.i1P(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V)
  %tmp_data_V = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty, 0
  %tmp_user_V = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty, 3
  %tmp_last_V = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty, 4
  %empty_27 = call i32 (...)* @_ssdm_op_SpecRegionEnd([20 x i8]* @p_str1819, i32 %tmp)
  br i1 %tmp_user_V, label %.preheader194.preheader, label %0

.preheader194.preheader:                          ; preds = %0
  %sof_1 = alloca i1, align 1
  store i1 true, i1* %sof_1, align 1
  br label %.preheader194

.preheader194:                                    ; preds = %.preheader194.preheader, %6
  %axi_last_V1 = phi i1 [ %axi_last_V_3, %6 ], [ %tmp_last_V, %.preheader194.preheader ]
  %axi_data_V1 = phi i32 [ %axi_data_V_3, %6 ], [ %tmp_data_V, %.preheader194.preheader ]
  %p_s = phi i12 [ %i_V, %6 ], [ 0, %.preheader194.preheader ]
  %exitcond3 = icmp eq i12 %p_s, %img_rows_V_read_1
  %i_V = add i12 %p_s, 1
  br i1 %exitcond3, label %7, label %1

; <label>:1                                       ; preds = %.preheader194
  call void (...)* @_ssdm_op_SpecLoopName([12 x i8]* @p_str1820) nounwind
  %tmp_s = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str1820)
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 480, i32 0, [1 x i8]* @p_str1806) nounwind
  br label %2

; <label>:2                                       ; preds = %.critedge195, %1
  %eol_1 = phi i1 [ %axi_last_V1, %1 ], [ %axi_last_V_2, %.critedge195 ]
  %axi_data_V_1 = phi i32 [ %axi_data_V1, %1 ], [ %p_Val2_s, %.critedge195 ]
  %p_3 = phi i12 [ 0, %1 ], [ %j_V, %.critedge195 ]
  %eol = phi i1 [ false, %1 ], [ %eol_2, %.critedge195 ]
  %exitcond = icmp eq i12 %p_3, %img_cols_V_read_1
  %j_V = add i12 %p_3, 1
  br i1 %exitcond, label %.preheader, label %3

; <label>:3                                       ; preds = %2
  %sof_1_load = load i1* %sof_1, align 1
  call void (...)* @_ssdm_op_SpecLoopName([11 x i8]* @p_str1821) nounwind
  %tmp_1 = call i32 (...)* @_ssdm_op_SpecRegionBegin([11 x i8]* @p_str1821)
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 640, i32 0, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  %brmerge = or i1 %sof_1_load, %eol
  %not_sof_2 = xor i1 %sof_1_load, true
  %axi_last_V_1_mux = or i1 %eol_1, %not_sof_2
  br i1 %brmerge, label %.critedge195, label %4

; <label>:4                                       ; preds = %3
  %empty_28 = call { i32, i4, i4, i1, i1, i1, i1 } @_ssdm_op_Read.axis.volatile.i32P.i4P.i4P.i1P.i1P.i1P.i1P(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V)
  %tmp_data_V_1 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_28, 0
  %tmp_last_V_1 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_28, 4
  br label %.critedge195

.critedge195:                                     ; preds = %4, %3
  %axi_last_V_2 = phi i1 [ %tmp_last_V_1, %4 ], [ %eol_1, %3 ]
  %p_Val2_s = phi i32 [ %tmp_data_V_1, %4 ], [ %axi_data_V_1, %3 ]
  %eol_2 = phi i1 [ %tmp_last_V_1, %4 ], [ %axi_last_V_1_mux, %3 ]
  call void (...)* @_ssdm_op_SpecLoopName([14 x i8]* @p_str1822) nounwind
  %tmp_3 = bitcast i32 %p_Val2_s to float
  %tmp_4 = call i32 (...)* @_ssdm_op_SpecRegionBegin([13 x i8]* @p_str1845)
  call void (...)* @_ssdm_op_SpecProtocol(i32 0, [1 x i8]* @p_str1806) nounwind
  call void @_ssdm_op_Write.ap_fifo.volatile.floatP(float* %img_data_stream_V, float %tmp_3)
  %empty_29 = call i32 (...)* @_ssdm_op_SpecRegionEnd([13 x i8]* @p_str1845, i32 %tmp_4)
  %empty_30 = call i32 (...)* @_ssdm_op_SpecRegionEnd([11 x i8]* @p_str1821, i32 %tmp_1)
  store i1 false, i1* %sof_1, align 1
  br label %2

.preheader:                                       ; preds = %2, %5
  %axi_last_V_3 = phi i1 [ %tmp_last_V_2, %5 ], [ %eol_1, %2 ]
  %axi_data_V_3 = phi i32 [ %tmp_data_V_2, %5 ], [ %axi_data_V_1, %2 ]
  %eol_3 = phi i1 [ %tmp_last_V_2, %5 ], [ %eol, %2 ]
  br i1 %eol_3, label %6, label %5

; <label>:5                                       ; preds = %.preheader
  call void (...)* @_ssdm_op_SpecLoopName([18 x i8]* @p_str1823) nounwind
  %tmp_2 = call i32 (...)* @_ssdm_op_SpecRegionBegin([18 x i8]* @p_str1823)
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 0, i32 0, [1 x i8]* @p_str1806) nounwind
  %empty_31 = call { i32, i4, i4, i1, i1, i1, i1 } @_ssdm_op_Read.axis.volatile.i32P.i4P.i4P.i1P.i1P.i1P.i1P(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V)
  %tmp_data_V_2 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_31, 0
  %tmp_last_V_2 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_31, 4
  %empty_32 = call i32 (...)* @_ssdm_op_SpecRegionEnd([18 x i8]* @p_str1823, i32 %tmp_2)
  br label %.preheader

; <label>:6                                       ; preds = %.preheader
  %empty_33 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str1820, i32 %tmp_s)
  br label %.preheader194

; <label>:7                                       ; preds = %.preheader194
  ret void
}

define internal fastcc void @"image_filter_AXIvideo2Mat<32, 480, 640, 5>.1"(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V, i12 %img_rows_V_read, i12 %img_cols_V_read, float* %img_data_stream_V) {
.critedge:
  call void (...)* @_ssdm_op_SpecInterface(i1* %AXI_video_strm_V_dest_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_user_V, i4* %AXI_video_strm_V_strb_V, i4* %AXI_video_strm_V_keep_V, i32* %AXI_video_strm_V_data_V, [5 x i8]* @p_str1808, i32 0, i32 0, i32 0, i32 0, [16 x i8]* @p_str1810, [1 x i8]* @p_str1806, [1 x i8]* @p_str1806)
  call void (...)* @_ssdm_op_SpecInterface(float* %img_data_stream_V, [8 x i8]* @str52, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str53, [1 x i8]* @str53, [8 x i8]* @str52)
  %img_cols_V_read_2 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %img_cols_V_read)
  %img_rows_V_read_2 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %img_rows_V_read)
  br label %0

; <label>:0                                       ; preds = %0, %.critedge
  call void (...)* @_ssdm_op_SpecLoopName([20 x i8]* @p_str1819) nounwind
  %tmp = call i32 (...)* @_ssdm_op_SpecRegionBegin([20 x i8]* @p_str1819)
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 0, i32 0, [1 x i8]* @p_str1806) nounwind
  %empty = call { i32, i4, i4, i1, i1, i1, i1 } @_ssdm_op_Read.axis.volatile.i32P.i4P.i4P.i1P.i1P.i1P.i1P(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V)
  %tmp_data_V = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty, 0
  %tmp_user_V = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty, 3
  %tmp_last_V = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty, 4
  %empty_34 = call i32 (...)* @_ssdm_op_SpecRegionEnd([20 x i8]* @p_str1819, i32 %tmp)
  br i1 %tmp_user_V, label %.preheader194.preheader, label %0

.preheader194.preheader:                          ; preds = %0
  %sof_1 = alloca i1, align 1
  store i1 true, i1* %sof_1, align 1
  br label %.preheader194

.preheader194:                                    ; preds = %.preheader194.preheader, %6
  %axi_last_V1 = phi i1 [ %axi_last_V_3, %6 ], [ %tmp_last_V, %.preheader194.preheader ]
  %axi_data_V1 = phi i32 [ %axi_data_V_3, %6 ], [ %tmp_data_V, %.preheader194.preheader ]
  %p_s = phi i12 [ %i_V, %6 ], [ 0, %.preheader194.preheader ]
  %exitcond3 = icmp eq i12 %p_s, %img_rows_V_read_2
  %i_V = add i12 %p_s, 1
  br i1 %exitcond3, label %7, label %1

; <label>:1                                       ; preds = %.preheader194
  call void (...)* @_ssdm_op_SpecLoopName([12 x i8]* @p_str1820) nounwind
  %tmp_s = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str1820)
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 480, i32 0, [1 x i8]* @p_str1806) nounwind
  br label %2

; <label>:2                                       ; preds = %.critedge195, %1
  %eol_1 = phi i1 [ %axi_last_V1, %1 ], [ %axi_last_V_2, %.critedge195 ]
  %axi_data_V_1 = phi i32 [ %axi_data_V1, %1 ], [ %p_Val2_s, %.critedge195 ]
  %p_3 = phi i12 [ 0, %1 ], [ %j_V, %.critedge195 ]
  %eol = phi i1 [ false, %1 ], [ %eol_2, %.critedge195 ]
  %exitcond = icmp eq i12 %p_3, %img_cols_V_read_2
  %j_V = add i12 %p_3, 1
  br i1 %exitcond, label %.preheader, label %3

; <label>:3                                       ; preds = %2
  %sof_1_load = load i1* %sof_1, align 1
  call void (...)* @_ssdm_op_SpecLoopName([11 x i8]* @p_str1821) nounwind
  %tmp_6 = call i32 (...)* @_ssdm_op_SpecRegionBegin([11 x i8]* @p_str1821)
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 640, i32 0, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  %brmerge = or i1 %sof_1_load, %eol
  %not_sof_2 = xor i1 %sof_1_load, true
  %axi_last_V_1_mux = or i1 %eol_1, %not_sof_2
  br i1 %brmerge, label %.critedge195, label %4

; <label>:4                                       ; preds = %3
  %empty_35 = call { i32, i4, i4, i1, i1, i1, i1 } @_ssdm_op_Read.axis.volatile.i32P.i4P.i4P.i1P.i1P.i1P.i1P(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V)
  %tmp_data_V_3 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_35, 0
  %tmp_last_V_3 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_35, 4
  br label %.critedge195

.critedge195:                                     ; preds = %4, %3
  %axi_last_V_2 = phi i1 [ %tmp_last_V_3, %4 ], [ %eol_1, %3 ]
  %p_Val2_s = phi i32 [ %tmp_data_V_3, %4 ], [ %axi_data_V_1, %3 ]
  %eol_2 = phi i1 [ %tmp_last_V_3, %4 ], [ %axi_last_V_1_mux, %3 ]
  call void (...)* @_ssdm_op_SpecLoopName([14 x i8]* @p_str1822) nounwind
  %tmp_4 = bitcast i32 %p_Val2_s to float
  %tmp_9 = call i32 (...)* @_ssdm_op_SpecRegionBegin([13 x i8]* @p_str1845)
  call void (...)* @_ssdm_op_SpecProtocol(i32 0, [1 x i8]* @p_str1806) nounwind
  call void @_ssdm_op_Write.ap_fifo.volatile.floatP(float* %img_data_stream_V, float %tmp_4)
  %empty_36 = call i32 (...)* @_ssdm_op_SpecRegionEnd([13 x i8]* @p_str1845, i32 %tmp_9)
  %empty_37 = call i32 (...)* @_ssdm_op_SpecRegionEnd([11 x i8]* @p_str1821, i32 %tmp_6)
  store i1 false, i1* %sof_1, align 1
  br label %2

.preheader:                                       ; preds = %2, %5
  %axi_last_V_3 = phi i1 [ %tmp_last_V_4, %5 ], [ %eol_1, %2 ]
  %axi_data_V_3 = phi i32 [ %tmp_data_V_4, %5 ], [ %axi_data_V_1, %2 ]
  %eol_3 = phi i1 [ %tmp_last_V_4, %5 ], [ %eol, %2 ]
  br i1 %eol_3, label %6, label %5

; <label>:5                                       ; preds = %.preheader
  call void (...)* @_ssdm_op_SpecLoopName([18 x i8]* @p_str1823) nounwind
  %tmp_7 = call i32 (...)* @_ssdm_op_SpecRegionBegin([18 x i8]* @p_str1823)
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 0, i32 0, [1 x i8]* @p_str1806) nounwind
  %empty_38 = call { i32, i4, i4, i1, i1, i1, i1 } @_ssdm_op_Read.axis.volatile.i32P.i4P.i4P.i1P.i1P.i1P.i1P(i32* %AXI_video_strm_V_data_V, i4* %AXI_video_strm_V_keep_V, i4* %AXI_video_strm_V_strb_V, i1* %AXI_video_strm_V_user_V, i1* %AXI_video_strm_V_last_V, i1* %AXI_video_strm_V_id_V, i1* %AXI_video_strm_V_dest_V)
  %tmp_data_V_4 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_38, 0
  %tmp_last_V_4 = extractvalue { i32, i4, i4, i1, i1, i1, i1 } %empty_38, 4
  %empty_39 = call i32 (...)* @_ssdm_op_SpecRegionEnd([18 x i8]* @p_str1823, i32 %tmp_7)
  br label %.preheader

; <label>:6                                       ; preds = %.preheader
  %empty_40 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str1820, i32 %tmp_s)
  br label %.preheader194

; <label>:7                                       ; preds = %.preheader194
  ret void
}

define internal fastcc void @image_filter_Resize_Test(i12 %p_src_rows_V_read, i12 %p_src_cols_V_read, float* %p_src_data_stream_V, i12 %p_dst_rows_V_read, i12 %p_dst_cols_V_read, float* %p_dst_data_stream_V) {
LineBuffer.exit:
  %row_wr = alloca i1, align 1
  %row_rd = alloca i1, align 1
  %pre_fx = alloca i16, align 2
  %pre_fy = alloca i16, align 2
  %x = alloca i16, align 2
  %win_val_0_val_1_0 = alloca float, align 4
  %win_val_0_val_1_0_5 = alloca float, align 4
  %win_val_1_val_1_0 = alloca float, align 4
  %win_val_1_val_1_0_3 = alloca float, align 4
  %tmp_122 = alloca float, align 4
  call void (...)* @_ssdm_op_SpecInterface(float* %p_dst_data_stream_V, [8 x i8]* @str56, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str57, [1 x i8]* @str57, [8 x i8]* @str56)
  call void (...)* @_ssdm_op_SpecInterface(float* %p_src_data_stream_V, [8 x i8]* @str52, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str53, [1 x i8]* @str53, [8 x i8]* @str52)
  %p_dst_cols_V_read_1 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %p_dst_cols_V_read)
  %p_dst_rows_V_read_1 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %p_dst_rows_V_read)
  %p_src_cols_V_read_1 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %p_src_cols_V_read)
  %p_src_rows_V_read_1 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %p_src_rows_V_read)
  %k_buf_val_val_0_0 = alloca [641 x float], align 4
  %k_buf_val_val_1_0 = alloca [641 x float], align 4
  %rbegin_i = call i32 (...)* @_ssdm_op_SpecRegionBegin([71 x i8]* @p_str1) nounwind
  %rend_i = call i32 (...)* @_ssdm_op_SpecRegionEnd([71 x i8]* @p_str1, i32 %rbegin_i) nounwind
  %srows_cast = zext i12 %p_src_rows_V_read_1 to i13
  %scols_cast = zext i12 %p_src_cols_V_read_1 to i13
  %tmp_s = call i28 @_ssdm_op_BitConcatenate.i28.i12.i16(i12 %p_dst_rows_V_read_1, i16 0)
  %tmp_2 = call i44 @_ssdm_op_BitConcatenate.i44.i12.i32(i12 %p_src_rows_V_read_1, i32 0)
  %tmp_20_cast = zext i28 %tmp_s to i44
  %tmp_3 = udiv i44 %tmp_2, %tmp_20_cast
  %row_rate_V = trunc i44 %tmp_3 to i32
  %tmp_4 = call i28 @_ssdm_op_BitConcatenate.i28.i12.i16(i12 %p_dst_cols_V_read_1, i16 0)
  %tmp_5 = call i44 @_ssdm_op_BitConcatenate.i44.i12.i32(i12 %p_src_cols_V_read_1, i32 0)
  %tmp_27_cast = zext i28 %tmp_4 to i44
  %tmp_6 = udiv i44 %tmp_5, %tmp_27_cast
  %col_rate_V = trunc i44 %tmp_6 to i32
  %tmp = call i1 @_ssdm_op_BitSelect.i1.i44.i32(i44 %tmp_3, i32 31)
  %p_neg1 = sub i32 0, %row_rate_V
  %p_lshr1 = call i31 @_ssdm_op_PartSelect.i31.i32.i32.i32(i32 %p_neg1, i32 1, i32 31)
  %tmp_11 = zext i31 %p_lshr1 to i32
  %p_neg_t1 = sub i32 0, %tmp_11
  %p_lshr_f1 = call i31 @_ssdm_op_PartSelect.i31.i44.i32.i32(i44 %tmp_3, i32 1, i32 31)
  %tmp_14 = zext i31 %p_lshr_f1 to i32
  %tmp_7 = select i1 %tmp, i32 %p_neg_t1, i32 %tmp_14
  %tmp_31_cast = sext i32 %tmp_7 to i33
  %p_Val2_1 = add i33 -32768, %tmp_31_cast
  %p_Val2_2 = call i20 @_ssdm_op_PartSelect.i20.i33.i32.i32(i33 %p_Val2_1, i32 6, i32 25)
  %tmp_50 = call i1 @_ssdm_op_BitSelect.i1.i33.i32(i33 %p_Val2_1, i32 5)
  %tmp_9 = zext i1 %tmp_50 to i20
  %p_Val2_13 = add i20 %p_Val2_2, %tmp_9
  %tmp_58 = call i1 @_ssdm_op_BitSelect.i1.i44.i32(i44 %tmp_6, i32 31)
  %p_neg = sub i32 0, %col_rate_V
  %p_lshr = call i31 @_ssdm_op_PartSelect.i31.i32.i32.i32(i32 %p_neg, i32 1, i32 31)
  %tmp_36 = zext i31 %p_lshr to i32
  %p_neg_t = sub i32 0, %tmp_36
  %p_lshr_f = call i31 @_ssdm_op_PartSelect.i31.i44.i32.i32(i44 %tmp_6, i32 1, i32 31)
  %tmp_41 = zext i31 %p_lshr_f to i32
  %tmp_1 = select i1 %tmp_58, i32 %p_neg_t, i32 %tmp_41
  %tmp_37_cast = sext i32 %tmp_1 to i33
  %p_Val2_5 = add i33 -32768, %tmp_37_cast
  %p_Val2_6 = call i20 @_ssdm_op_PartSelect.i20.i33.i32.i32(i33 %p_Val2_5, i32 6, i32 25)
  %tmp_74 = call i1 @_ssdm_op_BitSelect.i1.i33.i32(i33 %p_Val2_5, i32 5)
  %tmp_8 = zext i1 %tmp_74 to i20
  %p_Val2_14 = add i20 %p_Val2_6, %tmp_8
  %sx = add i13 -1, %scols_cast
  %tmp_41_cast = sext i13 %sx to i16
  %sy = add i13 -1, %srows_cast
  %tmp_42_cast = sext i13 %sy to i16
  %tmp_10 = zext i12 %p_dst_cols_V_read_1 to i13
  %tmp_12 = add i13 1, %tmp_10
  %tmp_13 = zext i12 %p_dst_rows_V_read_1 to i13
  %tmp_15 = add i13 1, %tmp_13
  %tmp_16 = icmp sgt i32 %row_rate_V, 65536
  %tmp_17 = icmp sgt i32 %col_rate_V, 65536
  %tmp_21 = call i26 @_ssdm_op_BitConcatenate.i26.i20.i6(i20 %p_Val2_13, i6 0)
  %tmp_60_cast = sext i26 %tmp_21 to i32
  %tmp_24 = call i26 @_ssdm_op_BitConcatenate.i26.i20.i6(i20 %p_Val2_14, i6 0)
  %tmp_62_cast = sext i26 %tmp_24 to i32
  store i16 0, i16* %x, align 2
  store i16 -10, i16* %pre_fy, align 2
  store i16 -10, i16* %pre_fx, align 2
  store i1 false, i1* %row_rd, align 1
  store i1 false, i1* %row_wr, align 1
  br label %.loopexit25

.loopexit25:                                      ; preds = %.preheader746, %LineBuffer.exit
  %p_Val2_9 = phi i13 [ 0, %LineBuffer.exit ], [ %i, %.preheader746 ]
  %exitcond1 = icmp eq i13 %p_Val2_9, %tmp_15
  %i = add i13 %p_Val2_9, 1
  br i1 %exitcond1, label %6, label %.preheader746.preheader

.preheader746.preheader:                          ; preds = %.loopexit25
  %tmp_18 = add i13 %p_Val2_9, -1
  %tmp_45_cast = sext i13 %tmp_18 to i16
  %tmp_19 = icmp eq i13 %p_Val2_9, 0
  %row_wr_2 = icmp ne i13 %p_Val2_9, 0
  %tmp_22 = call i29 @_ssdm_op_BitConcatenate.i29.i13.i16(i13 %p_Val2_9, i16 0)
  %tmp_51_cast = zext i29 %tmp_22 to i32
  br label %.preheader746

.preheader746:                                    ; preds = %._crit_edge758, %.preheader746.preheader
  %p_Val2_12 = phi i13 [ 0, %.preheader746.preheader ], [ %j, %._crit_edge758 ]
  %win_val_0_val_1_0_1 = load float* %win_val_0_val_1_0, align 4
  %exitcond = icmp eq i13 %p_Val2_12, %tmp_12
  %j = add i13 %p_Val2_12, 1
  br i1 %exitcond, label %.loopexit25, label %0

; <label>:0                                       ; preds = %.preheader746
  %tmp_20 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str1805)
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  br i1 %tmp_16, label %_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit, label %._crit_edge

_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit: ; preds = %0
  %tmp_23 = udiv i32 %tmp_51_cast, %row_rate_V
  %tmp_90 = trunc i32 %tmp_23 to i13
  br label %._crit_edge

._crit_edge:                                      ; preds = %_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit, %0
  %dy = phi i13 [ %tmp_90, %_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit ], [ %tmp_18, %0 ]
  br i1 %tmp_17, label %_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit21, label %1

_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit21: ; preds = %._crit_edge
  %tmp_25 = call i29 @_ssdm_op_BitConcatenate.i29.i13.i16(i13 %p_Val2_12, i16 0)
  %tmp_55_cast = zext i29 %tmp_25 to i32
  %tmp_26 = udiv i32 %tmp_55_cast, %col_rate_V
  %tmp_100 = trunc i32 %tmp_26 to i13
  br label %_ifconv

; <label>:1                                       ; preds = %._crit_edge
  %tmp_27 = add i13 %p_Val2_12, -1
  br label %_ifconv

_ifconv:                                          ; preds = %1, %_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit21
  %dx = phi i13 [ %tmp_100, %_ZNK13ap_fixed_baseILi33ELi17ELb1EL9ap_q_mode5EL9ap_o_mode3ELi0EEcvsEv.exit21 ], [ %tmp_27, %1 ]
  %row_wr_load = load i1* %row_wr, align 1
  %row_rd_load = load i1* %row_rd, align 1
  %pre_fx_load = load i16* %pre_fx, align 2
  %pre_fy_load = load i16* %pre_fy, align 2
  %x_load = load i16* %x, align 2
  %OP1_V = sext i13 %dy to i32
  %p_Val2_s = mul i32 %row_rate_V, %OP1_V
  %p_Val2_7 = add i32 %p_Val2_s, %tmp_60_cast
  %OP1_V_1 = sext i13 %dx to i32
  %p_Val2_10 = mul i32 %col_rate_V, %OP1_V_1
  %p_Val2_11 = add i32 %p_Val2_10, %tmp_62_cast
  %ret_V = call i16 @_ssdm_op_PartSelect.i16.i32.i32.i32(i32 %p_Val2_11, i32 16, i32 31)
  %tmp_108 = call i1 @_ssdm_op_BitSelect.i1.i32.i32(i32 %p_Val2_11, i32 31)
  %tmp_116 = trunc i32 %p_Val2_11 to i16
  %tmp_28 = icmp eq i16 %tmp_116, 0
  %ret_V_1 = add i16 1, %ret_V
  %p_6 = select i1 %tmp_28, i16 %ret_V, i16 %ret_V_1
  %sx_2 = select i1 %tmp_108, i16 %p_6, i16 %ret_V
  %ret_V_2 = call i16 @_ssdm_op_PartSelect.i16.i32.i32.i32(i32 %p_Val2_7, i32 16, i32 31)
  %tmp_117 = call i1 @_ssdm_op_BitSelect.i1.i32.i32(i32 %p_Val2_7, i32 31)
  %tmp_118 = trunc i32 %p_Val2_7 to i16
  %tmp_29 = icmp eq i16 %tmp_118, 0
  %ret_V_3 = add i16 1, %ret_V_2
  %p_7 = select i1 %tmp_29, i16 %ret_V_2, i16 %ret_V_3
  %sy_3 = select i1 %tmp_117, i16 %p_7, i16 %ret_V_2
  %tmp_30 = sext i32 %p_Val2_11 to i33
  %tmp_31 = call i32 @_ssdm_op_BitConcatenate.i32.i16.i16(i16 %sx_2, i16 0)
  %tmp_67_cast = sext i32 %tmp_31 to i33
  %r_V_6 = sub nsw i33 %tmp_30, %tmp_67_cast
  %tmp_32 = icmp sgt i33 %r_V_6, 0
  %tmp_119 = trunc i33 %r_V_6 to i18
  %tmp_33 = call i20 @_ssdm_op_BitConcatenate.i20.i18.i2(i18 %tmp_119, i2 0)
  %u_V = select i1 %tmp_32, i20 %tmp_33, i20 0
  %tmp_35 = sext i32 %p_Val2_7 to i33
  %tmp_37 = call i32 @_ssdm_op_BitConcatenate.i32.i16.i16(i16 %sy_3, i16 0)
  %tmp_73_cast = sext i32 %tmp_37 to i33
  %r_V_7 = sub nsw i33 %tmp_35, %tmp_73_cast
  %tmp_38 = icmp sgt i33 %r_V_7, 0
  %tmp_120 = trunc i33 %r_V_7 to i18
  %tmp_39 = call i20 @_ssdm_op_BitConcatenate.i20.i18.i2(i18 %tmp_120, i2 0)
  %v_V_2 = select i1 %tmp_38, i20 %tmp_39, i20 0
  %u1_V = sub i20 262144, %u_V
  %v1_V = sub i20 262144, %v_V_2
  %tmp_40 = icmp sgt i16 %sx_2, %tmp_41_cast
  %p_u_V = select i1 %tmp_40, i20 0, i20 %u_V
  %pre_fx_1 = select i1 %tmp_40, i16 %tmp_41_cast, i16 %sx_2
  %tmp_42 = icmp sgt i16 %sy_3, %tmp_42_cast
  %v_V = select i1 %tmp_42, i20 0, i20 %v_V_2
  %sy_4 = select i1 %tmp_42, i16 %tmp_42_cast, i16 %sy_3
  %tmp_43 = icmp eq i13 %p_Val2_12, 0
  %row_wr_1 = icmp eq i16 %sy_4, %tmp_45_cast
  %not_1 = icmp ne i16 %sy_4, %pre_fy_load
  %pre_fy_1_sy = select i1 %tmp_19, i16 %pre_fy_load, i16 %sy_4
  %x_1 = select i1 %tmp_43, i16 0, i16 %x_load
  %sel_tmp5 = and i1 %tmp_43, %tmp_16
  %sel_tmp6 = select i1 %sel_tmp5, i16 %pre_fy_load, i16 %pre_fy_1_sy
  %pre_fy_5 = select i1 %tmp_43, i16 %sel_tmp6, i16 %pre_fy_load
  %pre_fx_2 = select i1 %tmp_43, i16 -10, i16 %pre_fx_load
  %tmp4 = or i1 %not_1, %sel_tmp5
  %sel_tmp = or i1 %tmp4, %tmp_19
  %row_rd_5 = select i1 %tmp_43, i1 %sel_tmp, i1 %row_rd_load
  %row_wr_4 = select i1 %sel_tmp5, i1 %row_wr_1, i1 %row_wr_2
  %row_wr_3 = select i1 %tmp_43, i1 %row_wr_4, i1 %row_wr_load
  %tmp_44 = add i13 -1, %p_Val2_12
  %tmp_84_cast = sext i13 %tmp_44 to i16
  %col_wr = icmp eq i16 %pre_fx_1, %tmp_84_cast
  %not_s = icmp ne i16 %pre_fx_1, %pre_fx_2
  %pre_fx_2_sx = select i1 %tmp_43, i16 -10, i16 %pre_fx_1
  %col_wr_1 = icmp ne i13 %p_Val2_12, 0
  %pre_fx_5 = select i1 %tmp_17, i16 %pre_fx_2, i16 %pre_fx_2_sx
  %tmp5 = or i1 %not_s, %tmp_17
  %col_rd_2 = or i1 %tmp5, %tmp_43
  %col_wr_2 = select i1 %tmp_17, i1 %col_wr, i1 %col_wr_1
  br i1 %col_rd_2, label %.preheader745.0, label %._crit_edge752

.preheader745.0:                                  ; preds = %_ifconv
  %tmp_45 = sext i16 %x_1 to i64
  br i1 %row_rd_5, label %2, label %.preheader744.preheader

.preheader744.preheader:                          ; preds = %.preheader745.0
  %k_buf_val_val_0_0_addr_1 = getelementptr [641 x float]* %k_buf_val_val_0_0, i64 0, i64 %tmp_45
  %win_val_0_val_0_0 = load float* %k_buf_val_val_0_0_addr_1, align 4
  %k_buf_val_val_1_0_addr_1 = getelementptr [641 x float]* %k_buf_val_val_1_0, i64 0, i64 %tmp_45
  %win_val_1_val_0_0_1 = load float* %k_buf_val_val_1_0_addr_1, align 4
  store float %win_val_0_val_0_0, float* %win_val_0_val_1_0, align 4
  br label %.loopexit

; <label>:2                                       ; preds = %.preheader745.0
  %k_buf_val_val_1_0_addr = getelementptr [641 x float]* %k_buf_val_val_1_0, i64 0, i64 %tmp_45
  %k_buf_val_val_0_0_addr = getelementptr [641 x float]* %k_buf_val_val_0_0, i64 0, i64 %tmp_45
  %win_val_1_val_0_0 = load float* %k_buf_val_val_0_0_addr, align 4
  store float %win_val_1_val_0_0, float* %k_buf_val_val_1_0_addr, align 4
  %tmp_46 = icmp slt i16 %sy_4, %tmp_42_cast
  %tmp_47 = icmp slt i16 %pre_fx_1, %tmp_41_cast
  %or_cond_41 = and i1 %tmp_46, %tmp_47
  br i1 %or_cond_41, label %3, label %._crit_edge753

; <label>:3                                       ; preds = %2
  %tmp_34 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str1843)
  call void (...)* @_ssdm_op_SpecProtocol(i32 0, [1 x i8]* @p_str1806) nounwind
  %tmp_146 = call float @_ssdm_op_Read.ap_fifo.volatile.floatP(float* %p_src_data_stream_V)
  %empty = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str1843, i32 %tmp_34)
  store float %tmp_146, float* %k_buf_val_val_0_0_addr, align 4
  store float %tmp_146, float* %tmp_122, align 4
  store float %tmp_146, float* %win_val_0_val_1_0, align 4
  br label %.loopexit

._crit_edge753:                                   ; preds = %2
  br i1 %tmp_47, label %._crit_edge755, label %4

; <label>:4                                       ; preds = %._crit_edge753
  br i1 %tmp_46, label %5, label %.critedge

; <label>:5                                       ; preds = %4
  %tmp_122_load = load float* %tmp_122, align 4
  store float %tmp_122_load, float* %k_buf_val_val_0_0_addr, align 4
  br label %.loopexit

._crit_edge755:                                   ; preds = %._crit_edge753
  br i1 %tmp_46, label %.loopexit, label %.critedge

.critedge:                                        ; preds = %._crit_edge755, %4
  store float %win_val_1_val_0_0, float* %win_val_0_val_1_0, align 4
  br label %.loopexit

.loopexit:                                        ; preds = %.critedge, %._crit_edge755, %5, %3, %.preheader744.preheader
  %win_val_1_val_1_0_2 = phi float [ %win_val_1_val_0_0_1, %.preheader744.preheader ], [ %win_val_1_val_0_0, %3 ], [ %win_val_1_val_0_0, %._crit_edge755 ], [ %win_val_1_val_0_0, %.critedge ], [ %win_val_1_val_0_0, %5 ]
  %win_val_1_val_1_0_1 = load float* %win_val_1_val_1_0, align 4
  %x_2 = add i16 %x_1, 1
  store float %win_val_1_val_1_0_1, float* %win_val_1_val_1_0_3, align 4
  store float %win_val_1_val_1_0_2, float* %win_val_1_val_1_0, align 4
  store float %win_val_0_val_1_0_1, float* %win_val_0_val_1_0_5, align 4
  br label %._crit_edge752

._crit_edge752:                                   ; preds = %_ifconv, %.loopexit
  %storemerge = phi i16 [ %x_2, %.loopexit ], [ %x_1, %_ifconv ]
  store i16 %storemerge, i16* %x, align 2
  %brmerge_demorgan = and i1 %row_wr_3, %col_wr_2
  br i1 %brmerge_demorgan, label %.preheader.preheader_ifconv, label %._crit_edge758

.preheader.preheader_ifconv:                      ; preds = %._crit_edge752
  %win_val_0_val_1_0_load = load float* %win_val_0_val_1_0, align 4
  %win_val_0_val_1_0_5_load = load float* %win_val_0_val_1_0_5, align 4
  %win_val_1_val_1_0_load = load float* %win_val_1_val_1_0, align 4
  %win_val_1_val_1_0_3_load = load float* %win_val_1_val_1_0_3, align 4
  %OP2_V = sext i20 %u1_V to i84
  %OP2_V_1_cast = sext i20 %v1_V to i102
  %OP2_V_1 = sext i20 %v1_V to i84
  %d_assign = fpext float %win_val_1_val_1_0_3_load to double
  %ireg_V = bitcast double %d_assign to i64
  %tmp_123 = trunc i64 %ireg_V to i63
  %tmp_124 = call i1 @_ssdm_op_BitSelect.i1.i64.i32(i64 %ireg_V, i32 63)
  %p_Result_5 = call i11 @_ssdm_op_PartSelect.i11.i64.i32.i32(i64 %ireg_V, i32 52, i32 62)
  %tmp_48 = zext i11 %p_Result_5 to i12
  %tmp_125 = trunc i64 %ireg_V to i52
  %tmp_49 = call i53 @_ssdm_op_BitConcatenate.i53.i1.i52(i1 true, i52 %tmp_125)
  %p_Result_9 = zext i53 %tmp_49 to i54
  %man_V_1 = sub i54 0, %p_Result_9
  %p_Val2_17 = select i1 %tmp_124, i54 %man_V_1, i54 %p_Result_9
  %tmp_51 = icmp eq i63 %tmp_123, 0
  %F2 = sub i12 1075, %tmp_48
  %tmp_52 = icmp sgt i12 %F2, 32
  %tmp_53 = add i12 -32, %F2
  %tmp_54 = sub i12 32, %F2
  %sh_amt = select i1 %tmp_52, i12 %tmp_53, i12 %tmp_54
  %sh_amt_cast = sext i12 %sh_amt to i32
  %tmp_55 = icmp eq i12 %F2, 32
  %tmp_56 = sext i54 %p_Val2_17 to i64
  %tmp_57 = icmp ult i12 %sh_amt, 54
  %tmp_126 = call i6 @_ssdm_op_PartSelect.i6.i12.i32.i32(i12 %sh_amt, i32 6, i32 11)
  %icmp = icmp eq i6 %tmp_126, 0
  %tmp_59 = zext i32 %sh_amt_cast to i54
  %tmp_60 = ashr i54 %p_Val2_17, %tmp_59
  %p_8_cast = select i1 %tmp_124, i54 -1, i54 0
  %tmp_61 = zext i32 %sh_amt_cast to i64
  %tmp_62 = shl i64 %tmp_56, %tmp_61
  %p_Val2_20 = select i1 %tmp_57, i54 %tmp_60, i54 %p_8_cast
  %p_Val2_77_cast = sext i54 %p_Val2_20 to i55
  %tmp_63 = icmp sgt i12 %tmp_53, 54
  %tmp_64 = add i12 -33, %F2
  %tmp_135_cast = zext i12 %tmp_64 to i32
  %tmp_127 = call i1 @_ssdm_op_BitSelect.i1.i54.i32(i54 %p_Val2_17, i32 %tmp_135_cast)
  %qb = select i1 %tmp_63, i1 %tmp_124, i1 %tmp_127
  %tmp_139_cast = zext i1 %qb to i55
  %p_Val2_23 = add i55 %tmp_139_cast, %p_Val2_77_cast
  %p_Val2_78_cast = sext i55 %p_Val2_23 to i64
  %sel_tmp2 = xor i1 %tmp_51, true
  %sel_tmp3 = and i1 %tmp_55, %sel_tmp2
  %sel_tmp32_demorgan = or i1 %tmp_51, %tmp_55
  %sel_tmp4 = xor i1 %sel_tmp32_demorgan, true
  %sel_tmp7 = and i1 %tmp_52, %sel_tmp4
  %sel_tmp39_demorgan = or i1 %sel_tmp32_demorgan, %tmp_52
  %sel_tmp8 = xor i1 %sel_tmp39_demorgan, true
  %sel_tmp9 = and i1 %icmp, %sel_tmp8
  %newSel = select i1 %sel_tmp9, i64 %tmp_62, i64 %p_Val2_78_cast
  %or_cond = or i1 %sel_tmp9, %sel_tmp7
  %newSel7 = select i1 %sel_tmp3, i54 %p_Val2_17, i54 0
  %newSel7_cast = sext i54 %newSel7 to i64
  %newSel9 = select i1 %or_cond, i64 %newSel, i64 %newSel7_cast
  %OP1_V_2 = sext i64 %newSel9 to i84
  %r_V = mul nsw i84 %OP2_V, %OP1_V_2
  %OP1_V_3_cast = sext i84 %r_V to i102
  %p_Val2_24 = mul i102 %OP2_V_1_cast, %OP1_V_3_cast
  %d_assign_1 = fpext float %win_val_1_val_1_0_load to double
  %ireg_V_1 = bitcast double %d_assign_1 to i64
  %tmp_128 = trunc i64 %ireg_V_1 to i63
  %tmp_129 = call i1 @_ssdm_op_BitSelect.i1.i64.i32(i64 %ireg_V_1, i32 63)
  %p_Result_s = call i11 @_ssdm_op_PartSelect.i11.i64.i32.i32(i64 %ireg_V_1, i32 52, i32 62)
  %tmp_65 = zext i11 %p_Result_s to i12
  %tmp_130 = trunc i64 %ireg_V_1 to i52
  %tmp_66 = call i53 @_ssdm_op_BitConcatenate.i53.i1.i52(i1 true, i52 %tmp_130)
  %p_Result_1 = zext i53 %tmp_66 to i54
  %man_V_5 = sub i54 0, %p_Result_1
  %p_Val2_25 = select i1 %tmp_129, i54 %man_V_5, i54 %p_Result_1
  %tmp_67 = icmp eq i63 %tmp_128, 0
  %F2_1 = sub i12 1075, %tmp_65
  %tmp_68 = icmp sgt i12 %F2_1, 32
  %tmp_69 = add i12 -32, %F2_1
  %tmp_70 = sub i12 32, %F2_1
  %sh_amt_1 = select i1 %tmp_68, i12 %tmp_69, i12 %tmp_70
  %sh_amt_1_cast = sext i12 %sh_amt_1 to i32
  %tmp_71 = icmp eq i12 %F2_1, 32
  %tmp_72 = sext i54 %p_Val2_25 to i64
  %tmp_73 = icmp ult i12 %sh_amt_1, 54
  %tmp_131 = call i6 @_ssdm_op_PartSelect.i6.i12.i32.i32(i12 %sh_amt_1, i32 6, i32 11)
  %icmp1 = icmp eq i6 %tmp_131, 0
  %tmp_75 = zext i32 %sh_amt_1_cast to i54
  %tmp_76 = ashr i54 %p_Val2_25, %tmp_75
  %p_9_cast = select i1 %tmp_129, i54 -1, i54 0
  %tmp_77 = zext i32 %sh_amt_1_cast to i64
  %tmp_78 = shl i64 %tmp_72, %tmp_77
  %p_Val2_27 = select i1 %tmp_73, i54 %tmp_76, i54 %p_9_cast
  %p_Val2_82_cast = sext i54 %p_Val2_27 to i55
  %tmp_79 = icmp sgt i12 %tmp_69, 54
  %tmp_80 = add i12 -33, %F2_1
  %tmp_159_cast = zext i12 %tmp_80 to i32
  %tmp_132 = call i1 @_ssdm_op_BitSelect.i1.i54.i32(i54 %p_Val2_25, i32 %tmp_159_cast)
  %qb_1 = select i1 %tmp_79, i1 %tmp_129, i1 %tmp_132
  %tmp_163_cast = zext i1 %qb_1 to i55
  %p_Val2_28 = add i55 %tmp_163_cast, %p_Val2_82_cast
  %p_Val2_161_cast = sext i55 %p_Val2_28 to i64
  %sel_tmp1 = xor i1 %tmp_67, true
  %sel_tmp10 = and i1 %tmp_71, %sel_tmp1
  %sel_tmp50_demorgan = or i1 %tmp_67, %tmp_71
  %sel_tmp11 = xor i1 %sel_tmp50_demorgan, true
  %sel_tmp12 = and i1 %tmp_68, %sel_tmp11
  %sel_tmp57_demorgan = or i1 %sel_tmp50_demorgan, %tmp_68
  %sel_tmp13 = xor i1 %sel_tmp57_demorgan, true
  %sel_tmp14 = and i1 %icmp1, %sel_tmp13
  %newSel1 = select i1 %sel_tmp14, i64 %tmp_78, i64 %p_Val2_161_cast
  %or_cond1 = or i1 %sel_tmp14, %sel_tmp12
  %newSel2 = select i1 %sel_tmp10, i54 %p_Val2_25, i54 0
  %newSel13_cast = sext i54 %newSel2 to i64
  %newSel3 = select i1 %or_cond1, i64 %newSel1, i64 %newSel13_cast
  %OP1_V_4 = sext i64 %newSel3 to i84
  %r_V_1 = mul nsw i84 %OP2_V_1, %OP1_V_4
  %OP1_V_5_cast = sext i84 %r_V_1 to i102
  %OP2_V_5_cast = sext i20 %p_u_V to i102
  %p_Val2_29 = mul i102 %OP2_V_5_cast, %OP1_V_5_cast
  %tmp_164_cast = sext i102 %p_Val2_24 to i103
  %tmp_165_cast = sext i102 %p_Val2_29 to i103
  %p_Val2_30 = add i103 %tmp_165_cast, %tmp_164_cast
  %d_assign_2 = fpext float %win_val_0_val_1_0_5_load to double
  %ireg_V_2 = bitcast double %d_assign_2 to i64
  %tmp_133 = trunc i64 %ireg_V_2 to i63
  %tmp_134 = call i1 @_ssdm_op_BitSelect.i1.i64.i32(i64 %ireg_V_2, i32 63)
  %p_Result_2 = call i11 @_ssdm_op_PartSelect.i11.i64.i32.i32(i64 %ireg_V_2, i32 52, i32 62)
  %tmp_81 = zext i11 %p_Result_2 to i12
  %tmp_135 = trunc i64 %ireg_V_2 to i52
  %tmp_82 = call i53 @_ssdm_op_BitConcatenate.i53.i1.i52(i1 true, i52 %tmp_135)
  %p_Result_3 = zext i53 %tmp_82 to i54
  %man_V_9 = sub i54 0, %p_Result_3
  %p_Val2_31 = select i1 %tmp_134, i54 %man_V_9, i54 %p_Result_3
  %tmp_83 = icmp eq i63 %tmp_133, 0
  %F2_2 = sub i12 1075, %tmp_81
  %tmp_84 = icmp sgt i12 %F2_2, 32
  %tmp_85 = add i12 -32, %F2_2
  %tmp_86 = sub i12 32, %F2_2
  %sh_amt_2 = select i1 %tmp_84, i12 %tmp_85, i12 %tmp_86
  %sh_amt_2_cast = sext i12 %sh_amt_2 to i32
  %tmp_87 = icmp eq i12 %F2_2, 32
  %tmp_88 = sext i54 %p_Val2_31 to i64
  %tmp_89 = icmp ult i12 %sh_amt_2, 54
  %tmp_136 = call i6 @_ssdm_op_PartSelect.i6.i12.i32.i32(i12 %sh_amt_2, i32 6, i32 11)
  %icmp2 = icmp eq i6 %tmp_136, 0
  %tmp_91 = zext i32 %sh_amt_2_cast to i54
  %tmp_92 = ashr i54 %p_Val2_31, %tmp_91
  %p_10_cast = select i1 %tmp_134, i54 -1, i54 0
  %tmp_93 = zext i32 %sh_amt_2_cast to i64
  %tmp_94 = shl i64 %tmp_88, %tmp_93
  %p_Val2_32 = select i1 %tmp_89, i54 %tmp_92, i54 %p_10_cast
  %p_Val2_87_cast = sext i54 %p_Val2_32 to i55
  %tmp_95 = icmp sgt i12 %tmp_85, 54
  %tmp_96 = add i12 -33, %F2_2
  %tmp_185_cast = zext i12 %tmp_96 to i32
  %tmp_137 = call i1 @_ssdm_op_BitSelect.i1.i54.i32(i54 %p_Val2_31, i32 %tmp_185_cast)
  %qb_2 = select i1 %tmp_95, i1 %tmp_134, i1 %tmp_137
  %tmp_189_cast = zext i1 %qb_2 to i55
  %p_Val2_33 = add i55 %tmp_189_cast, %p_Val2_87_cast
  %p_Val2_221_cast = sext i55 %p_Val2_33 to i64
  %sel_tmp15 = xor i1 %tmp_83, true
  %sel_tmp16 = and i1 %tmp_87, %sel_tmp15
  %sel_tmp68_demorgan = or i1 %tmp_83, %tmp_87
  %sel_tmp17 = xor i1 %sel_tmp68_demorgan, true
  %sel_tmp18 = and i1 %tmp_84, %sel_tmp17
  %sel_tmp75_demorgan = or i1 %sel_tmp68_demorgan, %tmp_84
  %sel_tmp19 = xor i1 %sel_tmp75_demorgan, true
  %sel_tmp20 = and i1 %icmp2, %sel_tmp19
  %newSel4 = select i1 %sel_tmp20, i64 %tmp_94, i64 %p_Val2_221_cast
  %or_cond2 = or i1 %sel_tmp20, %sel_tmp18
  %newSel5 = select i1 %sel_tmp16, i54 %p_Val2_31, i54 0
  %newSel19_cast = sext i54 %newSel5 to i64
  %newSel6 = select i1 %or_cond2, i64 %newSel4, i64 %newSel19_cast
  %OP1_V_6 = sext i64 %newSel6 to i84
  %r_V_2 = mul nsw i84 %OP2_V, %OP1_V_6
  %OP1_V_7_cast = sext i84 %r_V_2 to i102
  %OP2_V_6_cast = sext i20 %v_V to i102
  %p_Val2_34 = mul i102 %OP2_V_6_cast, %OP1_V_7_cast
  %p_Val2_231_cast_cast = sext i102 %p_Val2_34 to i103
  %tmp_190_cast = sext i103 %p_Val2_30 to i104
  %d_assign_3 = fpext float %win_val_0_val_1_0_load to double
  %ireg_V_3 = bitcast double %d_assign_3 to i64
  %tmp_138 = trunc i64 %ireg_V_3 to i63
  %tmp_139 = call i1 @_ssdm_op_BitSelect.i1.i64.i32(i64 %ireg_V_3, i32 63)
  %p_Result_4 = call i11 @_ssdm_op_PartSelect.i11.i64.i32.i32(i64 %ireg_V_3, i32 52, i32 62)
  %tmp_99 = zext i11 %p_Result_4 to i12
  %tmp_140 = trunc i64 %ireg_V_3 to i52
  %tmp_97 = call i53 @_ssdm_op_BitConcatenate.i53.i1.i52(i1 true, i52 %tmp_140)
  %p_Result_6 = zext i53 %tmp_97 to i54
  %man_V_s = sub i54 0, %p_Result_6
  %p_Val2_35 = select i1 %tmp_139, i54 %man_V_s, i54 %p_Result_6
  %tmp_101 = icmp eq i63 %tmp_138, 0
  %F2_3 = sub i12 1075, %tmp_99
  %tmp_102 = icmp sgt i12 %F2_3, 32
  %tmp_103 = add i12 -32, %F2_3
  %tmp_104 = sub i12 32, %F2_3
  %sh_amt_3 = select i1 %tmp_102, i12 %tmp_103, i12 %tmp_104
  %sh_amt_3_cast = sext i12 %sh_amt_3 to i32
  %tmp_105 = icmp eq i12 %F2_3, 32
  %tmp_106 = sext i54 %p_Val2_35 to i64
  %tmp_107 = icmp ult i12 %sh_amt_3, 54
  %tmp_141 = call i6 @_ssdm_op_PartSelect.i6.i12.i32.i32(i12 %sh_amt_3, i32 6, i32 11)
  %icmp3 = icmp eq i6 %tmp_141, 0
  %tmp_109 = zext i32 %sh_amt_3_cast to i54
  %tmp_110 = ashr i54 %p_Val2_35, %tmp_109
  %tmp_142 = trunc i54 %tmp_110 to i53
  %p_11_cast_cast = select i1 %tmp_139, i53 -1, i53 0
  %tmp_111 = zext i32 %sh_amt_3_cast to i64
  %tmp_112 = shl i64 %tmp_106, %tmp_111
  %p_Val2_36 = select i1 %tmp_107, i53 %tmp_142, i53 %p_11_cast_cast
  %p_Val2_92_cast = sext i53 %p_Val2_36 to i54
  %tmp_113 = icmp sgt i12 %tmp_103, 54
  %tmp_114 = add i12 -33, %F2_3
  %tmp_211_cast = zext i12 %tmp_114 to i32
  %tmp_143 = call i1 @_ssdm_op_BitSelect.i1.i54.i32(i54 %p_Val2_35, i32 %tmp_211_cast)
  %qb_3 = select i1 %tmp_113, i1 %tmp_139, i1 %tmp_143
  %tmp_215_cast_cast = zext i1 %qb_3 to i54
  %p_Val2_26 = add i54 %tmp_215_cast_cast, %p_Val2_92_cast
  %p_Val2_26_cast = sext i54 %p_Val2_26 to i64
  %sel_tmp21 = xor i1 %tmp_101, true
  %sel_tmp22 = and i1 %tmp_105, %sel_tmp21
  %sel_tmp86_demorgan = or i1 %tmp_101, %tmp_105
  %sel_tmp23 = xor i1 %sel_tmp86_demorgan, true
  %sel_tmp24 = and i1 %tmp_102, %sel_tmp23
  %sel_tmp93_demorgan = or i1 %sel_tmp86_demorgan, %tmp_102
  %sel_tmp25 = xor i1 %sel_tmp93_demorgan, true
  %sel_tmp26 = and i1 %icmp3, %sel_tmp25
  %newSel8 = select i1 %sel_tmp26, i64 %tmp_112, i64 %p_Val2_26_cast
  %or_cond3 = or i1 %sel_tmp26, %sel_tmp24
  %newSel10 = select i1 %sel_tmp22, i54 %p_Val2_35, i54 0
  %newSel25_cast = sext i54 %newSel10 to i64
  %newSel11 = select i1 %or_cond3, i64 %newSel8, i64 %newSel25_cast
  %OP1_V_8 = sext i64 %newSel11 to i84
  %OP2_V_7 = sext i20 %p_u_V to i84
  %r_V_3 = mul nsw i84 %OP2_V_7, %OP1_V_8
  %OP1_V_9_cast = sext i84 %r_V_3 to i102
  %p_Val2_37 = mul i102 %OP2_V_6_cast, %OP1_V_9_cast
  %p_Val2_271_cast_cast = sext i102 %p_Val2_37 to i103
  %tmp6 = add i103 %p_Val2_271_cast_cast, %p_Val2_231_cast_cast
  %tmp6_cast = sext i103 %tmp6 to i104
  %p_Val2_38 = add i104 %tmp_190_cast, %tmp6_cast
  %p_Val2_39 = call i64 @_ssdm_op_PartSelect.i64.i104.i32.i32(i104 %p_Val2_38, i32 36, i32 99)
  %tmp_144 = call i1 @_ssdm_op_BitSelect.i1.i104.i32(i104 %p_Val2_38, i32 35)
  %tmp_115 = zext i1 %tmp_144 to i64
  %p_0 = add nsw i64 %tmp_115, %p_Val2_39
  %tmp_i_i = icmp eq i64 %p_0, 0
  %dp_1 = sitofp i64 %p_0 to float
  %res_V_1 = bitcast float %dp_1 to i32
  %exp_V = call i8 @_ssdm_op_PartSelect.i8.i32.i32.i32(i32 %res_V_1, i32 23, i32 30)
  %exp_V_2 = add i8 -32, %exp_V
  %p_Result_s_42 = call i32 @llvm.part.set.i32.i8(i32 %res_V_1, i8 %exp_V_2, i32 23, i32 30) nounwind
  %dp = bitcast i32 %p_Result_s_42 to float
  %tmp_145 = select i1 %tmp_i_i, float 0.000000e+00, float %dp
  %tmp_98 = call i32 (...)* @_ssdm_op_SpecRegionBegin([13 x i8]* @p_str1845)
  call void (...)* @_ssdm_op_SpecProtocol(i32 0, [1 x i8]* @p_str1806) nounwind
  call void @_ssdm_op_Write.ap_fifo.volatile.floatP(float* %p_dst_data_stream_V, float %tmp_145)
  %empty_43 = call i32 (...)* @_ssdm_op_SpecRegionEnd([13 x i8]* @p_str1845, i32 %tmp_98)
  br label %._crit_edge758

._crit_edge758:                                   ; preds = %.preheader.preheader_ifconv, %._crit_edge752
  %empty_44 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str1805, i32 %tmp_20)
  store i16 %pre_fy_5, i16* %pre_fy, align 2
  store i16 %pre_fx_5, i16* %pre_fx, align 2
  store i1 %row_rd_5, i1* %row_rd, align 1
  store i1 %row_wr_3, i1* %row_wr, align 1
  br label %.preheader746

; <label>:6                                       ; preds = %.loopexit25
  ret void
}

define internal fastcc float @image_filter_Block_.loopexit24.i_proc1(i64 %p_read) readnone {
newFuncRoot_ifconv:
  %p_read_1 = call i64 @_ssdm_op_Read.ap_auto.i64(i64 %p_read)
  %tmp_4 = icmp eq i64 %p_read_1, 0
  %dp_2 = sitofp i64 %p_read_1 to float
  %res_V_2 = bitcast float %dp_2 to i32
  %exp_V = call i8 @_ssdm_op_PartSelect.i8.i32.i32.i32(i32 %res_V_2, i32 23, i32 30)
  %exp_V_4 = add i8 %exp_V, -32
  %p_Result_s = call i32 @llvm.part.set.i32.i8(i32 %res_V_2, i8 %exp_V_4, i32 23, i32 30) nounwind
  %dp = bitcast i32 %p_Result_s to float
  %p_0_i_i_out = select i1 %tmp_4, float 0.000000e+00, float %dp
  ret float %p_0_i_i_out
}

define internal fastcc float @image_filter_sqrtf1(float %p_read) readonly {
  %p_read_2 = call float @_ssdm_op_Read.ap_auto.float(float %p_read)
  %tmp = call float @llvm.sqrt.f32(float %p_read_2)
  ret float %tmp
}

define internal fastcc { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } @image_filter_Block_Mat.exit2020_proc(i32 %rows, i32 %cols, i32 %rows2, i32 %cols2) readnone {
newFuncRoot:
  %cols2_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %cols2)
  %rows2_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %rows2)
  %cols_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %cols)
  %rows_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %rows)
  %img_0_1_rows_V = trunc i32 %rows_read to i12
  %img_0_1_cols_V = trunc i32 %cols_read to i12
  %img_resized_rows_V = trunc i32 %rows2_read to i12
  %img_resized_cols_V = trunc i32 %cols2_read to i12
  %mrv = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } undef, i12 %img_0_1_rows_V, 0
  %mrv_1 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv, i12 %img_0_1_rows_V, 1
  %mrv_2 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_1, i12 %img_0_1_cols_V, 2
  %mrv_3 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_2, i12 %img_0_1_cols_V, 3
  %mrv_4 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_3, i12 %img_resized_rows_V, 4
  %mrv_5 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_4, i12 %img_resized_rows_V, 5
  %mrv_6 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_5, i12 %img_resized_cols_V, 6
  %mrv_7 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_6, i12 %img_resized_cols_V, 7
  %mrv_8 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_7, i12 %img_resized_rows_V, 8
  %mrv_9 = insertvalue { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_8, i12 %img_resized_cols_V, 9
  ret { i12, i12, i12, i12, i12, i12, i12, i12, i12, i12 } %mrv_9
}

define internal fastcc i64 @image_filter_Loop_1_proc(float* %img_resized_data_stream_0_V, float* %img_0_2_data_stream_0_V, i12 %p_read, i12 %p_read1) {
newFuncRoot:
  %acc_V_1 = alloca i64, align 8
  %p_Val2_s = alloca i64, align 8
  call void (...)* @_ssdm_op_SpecInterface(float* %img_0_2_data_stream_0_V, [8 x i8]* @str60, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str61, [1 x i8]* @str61, [8 x i8]* @str60)
  call void (...)* @_ssdm_op_SpecInterface(float* %img_resized_data_stream_0_V, [8 x i8]* @str56, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @str57, [1 x i8]* @str57, [8 x i8]* @str56)
  %p_read_3 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %p_read1)
  %p_read_4 = call i12 @_ssdm_op_Read.ap_auto.i12(i12 %p_read)
  store i64 0, i64* %p_Val2_s, align 8
  store i64 0, i64* %acc_V_1, align 8
  br label %0

.loopexit24.i.exitStub:                           ; preds = %0
  %acc_V_1_load = load i64* %acc_V_1, align 8
  ret i64 %acc_V_1_load

; <label>:0                                       ; preds = %.loopexit.i, %newFuncRoot
  %i_0_i = phi i9 [ 0, %newFuncRoot ], [ %i, %.loopexit.i ]
  %i_0_i_cast_cast = zext i9 %i_0_i to i12
  %tmp_1 = icmp ult i9 %i_0_i, -32
  %tmp_3 = icmp ult i12 %i_0_i_cast_cast, %p_read_3
  %or_cond_45 = and i1 %tmp_1, %tmp_3
  %i = add i9 %i_0_i, 1
  br i1 %or_cond_45, label %.preheader.i, label %.loopexit24.i.exitStub

.loopexit.i:                                      ; preds = %1, %.preheader.i
  br label %0

.preheader.i:                                     ; preds = %0, %_ifconv
  %asd_0_i = phi i10 [ %asd, %_ifconv ], [ 0, %0 ]
  %asd_0_i_cast_cast = zext i10 %asd_0_i to i12
  %tmp_6 = icmp ult i10 %asd_0_i, -384
  %asd = add i10 %asd_0_i, 1
  br i1 %tmp_6, label %1, label %.loopexit.i

_ifconv:                                          ; preds = %1
  %p_Val2_load = load i64* %p_Val2_s, align 8
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1806) nounwind
  %tmp_9 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str1843)
  call void (...)* @_ssdm_op_SpecProtocol(i32 0, [1 x i8]* @p_str1806) nounwind
  %img_resized_data_stream_0_V_r = call float @_ssdm_op_Read.ap_fifo.volatile.floatP(float* %img_resized_data_stream_0_V)
  %empty = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str1843, i32 %tmp_9)
  %tmp_12 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str1843)
  call void (...)* @_ssdm_op_SpecProtocol(i32 0, [1 x i8]* @p_str1806) nounwind
  %img_0_2_data_stream_0_V_read = call float @_ssdm_op_Read.ap_fifo.volatile.floatP(float* %img_0_2_data_stream_0_V)
  %temp = fsub float %img_resized_data_stream_0_V_r, %img_0_2_data_stream_0_V_read
  %v_assign = fmul float %temp, %temp
  %d_assign = fpext float %v_assign to double
  %ireg_V = bitcast double %d_assign to i64
  %tmp_147 = trunc i64 %ireg_V to i63
  %empty_46 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str1843, i32 %tmp_12)
  %isneg = call i1 @_ssdm_op_BitSelect.i1.i64.i32(i64 %ireg_V, i32 63)
  %exp_tmp_V = call i11 @_ssdm_op_PartSelect.i11.i64.i32.i32(i64 %ireg_V, i32 52, i32 62)
  %tmp_15 = zext i11 %exp_tmp_V to i12
  %tmp_149 = trunc i64 %ireg_V to i52
  %tmp_16 = call i53 @_ssdm_op_BitConcatenate.i53.i1.i52(i1 true, i52 %tmp_149)
  %p_Result_s = zext i53 %tmp_16 to i54
  %man_V_1 = sub i54 0, %p_Result_s
  %p_Val2_44 = select i1 %isneg, i54 %man_V_1, i54 %p_Result_s
  %tmp_18 = icmp eq i63 %tmp_147, 0
  %F2 = sub i12 1075, %tmp_15
  %tmp_20 = icmp sgt i12 %F2, 32
  %tmp_21 = add i12 -32, %F2
  %tmp_22 = sub i12 32, %F2
  %sh_amt = select i1 %tmp_20, i12 %tmp_21, i12 %tmp_22
  %sh_amt_cast = sext i12 %sh_amt to i32
  %tmp_23 = icmp eq i12 %F2, 32
  %tmp_24 = sext i54 %p_Val2_44 to i64
  %tmp_25 = icmp ult i12 %sh_amt, 54
  %tmp_150 = call i6 @_ssdm_op_PartSelect.i6.i12.i32.i32(i12 %sh_amt, i32 6, i32 11)
  %icmp = icmp eq i6 %tmp_150, 0
  %tmp_28 = zext i32 %sh_amt_cast to i54
  %tmp_29 = ashr i54 %p_Val2_44, %tmp_28
  %this_assign_cast = select i1 %isneg, i54 -1, i54 0
  %tmp_31 = zext i32 %sh_amt_cast to i64
  %tmp_32 = shl i64 %tmp_24, %tmp_31
  %p_Val2_3 = select i1 %tmp_25, i54 %tmp_29, i54 %this_assign_cast
  %p_Val2_3_cast = sext i54 %p_Val2_3 to i55
  %tmp_33 = icmp sgt i12 %tmp_21, 54
  %tmp_34 = add i12 -33, %F2
  %tmp_34_cast = zext i12 %tmp_34 to i32
  %tmp_151 = call i1 @_ssdm_op_BitSelect.i1.i54.i32(i54 %p_Val2_44, i32 %tmp_34_cast)
  %qb = select i1 %tmp_33, i1 %isneg, i1 %tmp_151
  %tmp_37_cast = zext i1 %qb to i55
  %p_Val2_5 = add i55 %tmp_37_cast, %p_Val2_3_cast
  %p_Val2_5_cast = sext i55 %p_Val2_5 to i64
  %sel_tmp1 = xor i1 %tmp_18, true
  %sel_tmp2 = and i1 %tmp_23, %sel_tmp1
  %sel_tmp6_demorgan = or i1 %tmp_18, %tmp_23
  %sel_tmp6 = xor i1 %sel_tmp6_demorgan, true
  %sel_tmp7 = and i1 %tmp_20, %sel_tmp6
  %sel_tmp13_demorgan = or i1 %sel_tmp6_demorgan, %tmp_20
  %sel_tmp13 = xor i1 %sel_tmp13_demorgan, true
  %sel_tmp14 = and i1 %icmp, %sel_tmp13
  %newSel = select i1 %sel_tmp14, i64 %tmp_32, i64 %p_Val2_5_cast
  %or_cond = or i1 %sel_tmp14, %sel_tmp7
  %newSel3 = select i1 %sel_tmp2, i54 %p_Val2_44, i54 0
  %newSel3_cast = sext i54 %newSel3 to i64
  %p_Val2_45 = select i1 %or_cond, i64 %newSel, i64 %newSel3_cast
  %acc_V = add i64 %p_Val2_load, %p_Val2_45
  %empty_47 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str1807, i32 %tmp)
  store i64 %acc_V, i64* %p_Val2_s, align 8
  store i64 %acc_V, i64* %acc_V_1, align 8
  br label %.preheader.i

; <label>:1                                       ; preds = %.preheader.i
  %tmp = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str1807)
  %tmp_8 = icmp ult i12 %asd_0_i_cast_cast, %p_read_4
  br i1 %tmp_8, label %_ifconv, label %.loopexit.i
}

define weak i26 @_ssdm_op_BitConcatenate.i26.i20.i6(i20, i6) nounwind readnone {
entry:
  %empty = zext i20 %0 to i26
  %empty_48 = zext i6 %1 to i26
  %empty_49 = shl i26 %empty, 6
  %empty_50 = or i26 %empty_49, %empty_48
  ret i26 %empty_50
}

define weak i20 @_ssdm_op_PartSelect.i20.i33.i32.i32(i33, i32, i32) nounwind readnone {
entry:
  %empty = call i33 @llvm.part.select.i33(i33 %0, i32 %1, i32 %2)
  %empty_51 = trunc i33 %empty to i20
  ret i20 %empty_51
}

define weak i28 @_ssdm_op_BitConcatenate.i28.i12.i16(i12, i16) nounwind readnone {
entry:
  %empty = zext i12 %0 to i28
  %empty_52 = zext i16 %1 to i28
  %empty_53 = shl i28 %empty, 16
  %empty_54 = or i28 %empty_53, %empty_52
  ret i28 %empty_54
}

define weak i31 @_ssdm_op_PartSelect.i31.i32.i32.i32(i32, i32, i32) nounwind readnone {
entry:
  %empty = call i32 @llvm.part.select.i32(i32 %0, i32 %1, i32 %2)
  %empty_55 = trunc i32 %empty to i31
  ret i31 %empty_55
}

define weak i31 @_ssdm_op_PartSelect.i31.i44.i32.i32(i44, i32, i32) nounwind readnone {
entry:
  %empty = call i44 @llvm.part.select.i44(i44 %0, i32 %1, i32 %2)
  %empty_56 = trunc i44 %empty to i31
  ret i31 %empty_56
}

define weak i44 @_ssdm_op_BitConcatenate.i44.i12.i32(i12, i32) nounwind readnone {
entry:
  %empty = zext i12 %0 to i44
  %empty_57 = zext i32 %1 to i44
  %empty_58 = shl i44 %empty, 32
  %empty_59 = or i44 %empty_58, %empty_57
  ret i44 %empty_59
}

define weak i29 @_ssdm_op_BitConcatenate.i29.i13.i16(i13, i16) nounwind readnone {
entry:
  %empty = zext i13 %0 to i29
  %empty_60 = zext i16 %1 to i29
  %empty_61 = shl i29 %empty, 16
  %empty_62 = or i29 %empty_61, %empty_60
  ret i29 %empty_62
}

define weak i20 @_ssdm_op_BitConcatenate.i20.i18.i2(i18, i2) nounwind readnone {
entry:
  %empty = zext i18 %0 to i20
  %empty_63 = zext i2 %1 to i20
  %empty_64 = shl i20 %empty, 2
  %empty_65 = or i20 %empty_64, %empty_63
  ret i20 %empty_65
}

define weak i32 @_ssdm_op_BitConcatenate.i32.i16.i16(i16, i16) nounwind readnone {
entry:
  %empty = zext i16 %0 to i32
  %empty_66 = zext i16 %1 to i32
  %empty_67 = shl i32 %empty, 16
  %empty_68 = or i32 %empty_67, %empty_66
  ret i32 %empty_68
}

define weak i64 @_ssdm_op_PartSelect.i64.i104.i32.i32(i104, i32, i32) nounwind readnone {
entry:
  %empty = call i104 @llvm.part.select.i104(i104 %0, i32 %1, i32 %2)
  %empty_69 = trunc i104 %empty to i64
  ret i64 %empty_69
}

define weak i32 @_ssdm_op_Read.s_axilite.i32(i32) {
entry:
  ret i32 %0
}

define weak float @_ssdm_op_Read.ap_auto.float(float) {
entry:
  ret float %0
}

define weak i64 @_ssdm_op_Read.ap_auto.i64(i64) {
entry:
  ret i64 %0
}

define weak i12 @_ssdm_op_Read.ap_auto.i12(i12) {
entry:
  ret i12 %0
}

define weak float @_ssdm_op_Read.ap_fifo.volatile.floatP(float*) {
entry:
  %empty = call float @_autotb_FifoRead_float(float* %0)
  ret float %empty
}

define weak void @_ssdm_op_Write.ap_fifo.volatile.floatP(float*, float) {
entry:
  %empty = call float @_autotb_FifoWrite_float(float* %0, float %1)
  ret void
}

define weak { i32, i4, i4, i1, i1, i1, i1 } @_ssdm_op_Read.axis.volatile.i32P.i4P.i4P.i1P.i1P.i1P.i1P(i32*, i4*, i4*, i1*, i1*, i1*, i1*) {
entry:
  %empty = load i32* %0
  %empty_70 = load i4* %1
  %empty_71 = load i4* %2
  %empty_72 = load i1* %3
  %empty_73 = load i1* %4
  %empty_74 = load i1* %5
  %empty_75 = load i1* %6
  %mrv_0 = insertvalue { i32, i4, i4, i1, i1, i1, i1 } undef, i32 %empty, 0
  %mrv1 = insertvalue { i32, i4, i4, i1, i1, i1, i1 } %mrv_0, i4 %empty_70, 1
  %mrv2 = insertvalue { i32, i4, i4, i1, i1, i1, i1 } %mrv1, i4 %empty_71, 2
  %mrv3 = insertvalue { i32, i4, i4, i1, i1, i1, i1 } %mrv2, i1 %empty_72, 3
  %mrv4 = insertvalue { i32, i4, i4, i1, i1, i1, i1 } %mrv3, i1 %empty_73, 4
  %mrv5 = insertvalue { i32, i4, i4, i1, i1, i1, i1 } %mrv4, i1 %empty_74, 5
  %mrv6 = insertvalue { i32, i4, i4, i1, i1, i1, i1 } %mrv5, i1 %empty_75, 6
  ret { i32, i4, i4, i1, i1, i1, i1 } %mrv6
}

define weak i32 @_ssdm_op_Read.ap_auto.i32(i32) {
entry:
  ret i32 %0
}

define weak i1 @_ssdm_op_BitSelect.i1.i44.i32(i44, i32) nounwind readnone {
entry:
  %empty = zext i32 %1 to i44
  %empty_76 = shl i44 1, %empty
  %empty_77 = and i44 %0, %empty_76
  %empty_78 = icmp ne i44 %empty_77, 0
  ret i1 %empty_78
}

define weak i1 @_ssdm_op_BitSelect.i1.i33.i32(i33, i32) nounwind readnone {
entry:
  %empty = zext i32 %1 to i33
  %empty_79 = shl i33 1, %empty
  %empty_80 = and i33 %0, %empty_79
  %empty_81 = icmp ne i33 %empty_80, 0
  ret i1 %empty_81
}

define weak i1 @_ssdm_op_BitSelect.i1.i32.i32(i32, i32) nounwind readnone {
entry:
  %empty = shl i32 1, %1
  %empty_82 = and i32 %0, %empty
  %empty_83 = icmp ne i32 %empty_82, 0
  ret i1 %empty_83
}

define weak i1 @_ssdm_op_BitSelect.i1.i64.i32(i64, i32) nounwind readnone {
entry:
  %empty = zext i32 %1 to i64
  %empty_84 = shl i64 1, %empty
  %empty_85 = and i64 %0, %empty_84
  %empty_86 = icmp ne i64 %empty_85, 0
  ret i1 %empty_86
}

define weak i6 @_ssdm_op_PartSelect.i6.i12.i32.i32(i12, i32, i32) nounwind readnone {
entry:
  %empty = call i12 @llvm.part.select.i12(i12 %0, i32 %1, i32 %2)
  %empty_87 = trunc i12 %empty to i6
  ret i6 %empty_87
}

define weak i1 @_ssdm_op_BitSelect.i1.i54.i32(i54, i32) nounwind readnone {
entry:
  %empty = zext i32 %1 to i54
  %empty_88 = shl i54 1, %empty
  %empty_89 = and i54 %0, %empty_88
  %empty_90 = icmp ne i54 %empty_89, 0
  ret i1 %empty_90
}

define weak i1 @_ssdm_op_BitSelect.i1.i104.i32(i104, i32) nounwind readnone {
entry:
  %empty = zext i32 %1 to i104
  %empty_91 = shl i104 1, %empty
  %empty_92 = and i104 %0, %empty_91
  %empty_93 = icmp ne i104 %empty_92, 0
  ret i1 %empty_93
}

declare float @_autotb_FifoRead_float(float*)

declare float @_autotb_FifoWrite_float(float*, float)

declare i32 @llvm.part.select.i32(i32, i32, i32) nounwind readnone

declare i64 @llvm.part.select.i64(i64, i32, i32) nounwind readnone

declare i33 @llvm.part.select.i33(i33, i32, i32) nounwind readnone

declare i44 @llvm.part.select.i44(i44, i32, i32) nounwind readnone

declare i104 @llvm.part.select.i104(i104, i32, i32) nounwind readnone

declare i12 @llvm.part.select.i12(i12, i32, i32) nounwind readnone

declare i32 @_ssdm_op_PartSelect.i32.i44.i32.i32(i44, i32, i32) nounwind readnone

declare i13 @_ssdm_op_PartSelect.i13.i32.i32.i32(i32, i32, i32) nounwind readnone

declare i18 @_ssdm_op_PartSelect.i18.i33.i32.i32(i33, i32, i32) nounwind readnone

declare i53 @_ssdm_op_PartSelect.i53.i54.i32.i32(i54, i32, i32) nounwind readnone

declare i52 @_ssdm_op_PartSelect.i52.i64.i32.i32(i64, i32, i32) nounwind readnone

declare i63 @_ssdm_op_PartSelect.i63.i64.i32.i32(i64, i32, i32) nounwind readnone

declare i12 @_ssdm_op_PartSelect.i12.i32.i32.i32(i32, i32, i32) nounwind readnone

!hls.encrypted.func = !{}
!llvm.map.gv = !{!0}

!0 = metadata !{metadata !1, [1 x i32]* @llvm_global_ctors_0}
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0, i32 31, metadata !3}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !"llvm.global_ctors.0", metadata !5, metadata !"", i32 0, i32 31}
!5 = metadata !{metadata !6}
!6 = metadata !{i32 0, i32 0, i32 1}
!7 = metadata !{metadata !8}
!8 = metadata !{i32 0, i32 31, metadata !9}
!9 = metadata !{metadata !10}
!10 = metadata !{metadata !"input_stream.V.data.V", metadata !5, metadata !"uint32", i32 0, i32 31}
!11 = metadata !{metadata !12}
!12 = metadata !{i32 0, i32 3, metadata !13}
!13 = metadata !{metadata !14}
!14 = metadata !{metadata !"input_stream.V.keep.V", metadata !5, metadata !"uint4", i32 0, i32 3}
!15 = metadata !{metadata !16}
!16 = metadata !{i32 0, i32 3, metadata !17}
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !"input_stream.V.strb.V", metadata !5, metadata !"uint4", i32 0, i32 3}
!19 = metadata !{metadata !20}
!20 = metadata !{i32 0, i32 0, metadata !21}
!21 = metadata !{metadata !22}
!22 = metadata !{metadata !"input_stream.V.user.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!23 = metadata !{metadata !24}
!24 = metadata !{i32 0, i32 0, metadata !25}
!25 = metadata !{metadata !26}
!26 = metadata !{metadata !"input_stream.V.last.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!27 = metadata !{metadata !28}
!28 = metadata !{i32 0, i32 0, metadata !29}
!29 = metadata !{metadata !30}
!30 = metadata !{metadata !"input_stream.V.id.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!31 = metadata !{metadata !32}
!32 = metadata !{i32 0, i32 0, metadata !33}
!33 = metadata !{metadata !34}
!34 = metadata !{metadata !"input_stream.V.dest.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!35 = metadata !{metadata !36}
!36 = metadata !{i32 0, i32 31, metadata !37}
!37 = metadata !{metadata !38}
!38 = metadata !{metadata !"input2.V.data.V", metadata !5, metadata !"uint32", i32 0, i32 31}
!39 = metadata !{metadata !40}
!40 = metadata !{i32 0, i32 3, metadata !41}
!41 = metadata !{metadata !42}
!42 = metadata !{metadata !"input2.V.keep.V", metadata !5, metadata !"uint4", i32 0, i32 3}
!43 = metadata !{metadata !44}
!44 = metadata !{i32 0, i32 3, metadata !45}
!45 = metadata !{metadata !46}
!46 = metadata !{metadata !"input2.V.strb.V", metadata !5, metadata !"uint4", i32 0, i32 3}
!47 = metadata !{metadata !48}
!48 = metadata !{i32 0, i32 0, metadata !49}
!49 = metadata !{metadata !50}
!50 = metadata !{metadata !"input2.V.user.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!51 = metadata !{metadata !52}
!52 = metadata !{i32 0, i32 0, metadata !53}
!53 = metadata !{metadata !54}
!54 = metadata !{metadata !"input2.V.last.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!55 = metadata !{metadata !56}
!56 = metadata !{i32 0, i32 0, metadata !57}
!57 = metadata !{metadata !58}
!58 = metadata !{metadata !"input2.V.id.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!59 = metadata !{metadata !60}
!60 = metadata !{i32 0, i32 0, metadata !61}
!61 = metadata !{metadata !62}
!62 = metadata !{metadata !"input2.V.dest.V", metadata !5, metadata !"uint1", i32 0, i32 0}
!63 = metadata !{metadata !64}
!64 = metadata !{i32 0, i32 31, metadata !65}
!65 = metadata !{metadata !66}
!66 = metadata !{metadata !"rows", metadata !67, metadata !"int", i32 0, i32 31}
!67 = metadata !{metadata !68}
!68 = metadata !{i32 0, i32 0, i32 0}
!69 = metadata !{metadata !70}
!70 = metadata !{i32 0, i32 31, metadata !71}
!71 = metadata !{metadata !72}
!72 = metadata !{metadata !"cols", metadata !67, metadata !"int", i32 0, i32 31}
!73 = metadata !{metadata !74}
!74 = metadata !{i32 0, i32 31, metadata !75}
!75 = metadata !{metadata !76}
!76 = metadata !{metadata !"rows2", metadata !67, metadata !"int", i32 0, i32 31}
!77 = metadata !{metadata !78}
!78 = metadata !{i32 0, i32 31, metadata !79}
!79 = metadata !{metadata !80}
!80 = metadata !{metadata !"cols2", metadata !67, metadata !"int", i32 0, i32 31}
!81 = metadata !{metadata !82}
!82 = metadata !{i32 0, i32 31, metadata !83}
!83 = metadata !{metadata !84}
!84 = metadata !{metadata !"return", metadata !85, metadata !"float", i32 0, i32 31}
!85 = metadata !{metadata !86}
!86 = metadata !{i32 0, i32 1, i32 0}
