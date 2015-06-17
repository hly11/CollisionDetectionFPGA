 #ifndef _TOP_H_
 #define _TOP_H_

 #include "hls_video.h"

 // maximum image size
 //#define MAX_WIDTH  1920
 //#define MAX_HEIGHT 1080

 // typedef video library core structures
 typedef hls::stream<ap_axiu<32,1,1,1> >               AXI_STREAM;
 //typedef hls::Scalar<3, unsigned char>                 RGB_PIXEL;
 //typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32SC1>    GRAY_IMAGE;

 // top level function for HW synthesis
 float image_filter(AXI_STREAM& src_axi, AXI_STREAM& dst_axi, int rows, int cols, int FILTER_SIZE, int do_filter);
 //template<int IMG_H, int IMG_W, int FILTER_SIZE> void FilterTest(hls::Mat<IMG_H+FILTER_SIZE, IMG_W+FILTER_SIZE, HLS_32FC1> &in, hls::Mat<IMG_H, IMG_W, HLS_32FC1> &out);
 //template<int IMG_H, int IMG_W, int SIZE> void PadImage(hls::Mat<IMG_H, IMG_W, HLS_32FC1> &in, hls::Mat<IMG_H+SIZE, IMG_W+SIZE, HLS_32FC1> &out)

 #endif
