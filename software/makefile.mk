# Makefile for visual studio using nmake

CPPFLAGS = /W4 /EHsc /Iinclude/opencv /Iinclude /DNOMINMAX
LDFLAGS = 
LDLIBS =

# Turn on optimisations
CPPFLAGS = $(CPPFLAGS) /O2

# TODO : Indicate where you have put the TBB installer
TBB_DIR = ..\tbb43_20150209oss

TBB_INC_DIR = $(TBB_DIR)\include

# TODO: Choose the correct library for your build
TBB_LIB_DIR = $(TBB_DIR)\lib\intel64\vc12

CPPFLAGS = $(CPPFLAGS) /I$(TBB_INC_DIR)
LDFLAGS = $(LDFLAGS) /LIBPATH:$(TBB_LIB_DIR) /LIBPATH:x64/vc12/staticlib

# The very basic parts
FOURIER_CORE_OBJS = src/fasthessian.obj src/integral.obj src/ipoint.cpp src/surf.cpp src/utils.cpp

# implementations
#FOURIER_IMPLEMENTATION_OBJS =  src/fast_fourier_transform.obj	src/direct_fourier_transform.obj src/hly11/direct_fourier_transform_parfor.obj src/hly11/fast_fourier_transform_taskgroup.obj src/hly11/direct_fourier_transform_chunked.obj src/hly11/fast_fourier_transform_parfor.obj src/hly11/fast_fourier_transform_combined.obj src/hly11/fast_fourier_transform_opt.obj

#FOURIER_OBJS = $(FOURIER_CORE_OBJS) $(FOURIER_IMPLEMENTATION_OBJS)

.cpp.obj :
	$(CPP) $(CPPFLAGS) /c $< /Fo$@

#bin\main : src/main.cpp $(FOURIER_CORE_OBJS)
#	-mkdir bin
#	$(CPP) $(CPPFLAGS) $** /Fe$@ opencv_ts300.lib opencv_world300.lib /link $(LDFLAGS) $(LDLIBS)
	
bin\main : src/main.cpp $(FOURIER_CORE_OBJS)
	-mkdir bin
	$(CPP) $(CPPFLAGS) $** /Fe$@ kernel32.lib  user32.lib  gdi32.lib  winspool.lib  comdlg32.lib  advapi32.lib  shell32.lib  ole32.lib  oleaut32.lib  uuid.lib  odbc32.lib  odbccp32.lib IlmImf.lib IlmImfd.lib ippicvmt.lib libjasper.lib libjasperd.lib libjpeg.lib libjpegd.lib libpng.lib libpngd.lib libtiff.lib libtiffd.lib libwebp.lib libwebpd.lib opencv_calib3d300.lib opencv_calib3d300d.lib opencv_core300.lib opencv_core300d.lib opencv_features2d300.lib opencv_features2d300d.lib opencv_flann300.lib opencv_flann300d.lib opencv_hal300.lib opencv_hal300d.lib opencv_highgui300.lib opencv_highgui300d.lib opencv_imgcodecs300.lib opencv_imgcodecs300d.lib opencv_imgproc300.lib opencv_imgproc300d.lib opencv_ml300.lib opencv_ml300d.lib opencv_objdetect300.lib opencv_objdetect300d.lib opencv_photo300.lib opencv_photo300d.lib opencv_shape300.lib opencv_shape300d.lib opencv_stitching300.lib opencv_stitching300d.lib opencv_superres300.lib opencv_superres300d.lib opencv_ts300.lib opencv_ts300d.lib opencv_video300.lib opencv_video300d.lib opencv_videoio300.lib opencv_videoio300d.lib opencv_videostab300.lib opencv_videostab300d.lib zlib.lib zlibd.lib /link $(LDFLAGS) $(LDLIBS)

all : bin\main
