/*********************************************************** 
*  --- OpenSURF ---                                       *
*  This library is distributed under the GNU GPL. Please   *
*  use the contact form at http://www.chrisevansdev.com    *
*  for more information.                                   *
*                                                          *
*  C. Evans, Research Into Robust Visual Features,         *
*  MSc University of Bristol, 2008.                        *
*                                                          *
************************************************************/

#include "integral.h"
#include "ipoint.h"
#include "utils.h"

#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <iomanip>

#include "xVDMA_.h"
#include "ximage_filter_fh.h"

#include "responselayer.h"
#include "fasthessian.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv/cv.h"

float * responselayers[6];
int responselayers_init;

//using namespace std;

//-------------------------------------------------------

//! Constructor without image
FastHessian::FastHessian(std::vector<Ipoint> &ipts, 
                         const int octaves, const int intervals, const int init_sample, 
                         const float thresh) 
                         : ipts(ipts), i_width(0), i_height(0)
{
  // Save parameter set
  saveParameters(octaves, intervals, init_sample, thresh);
}

//-------------------------------------------------------

//! Constructor with image
FastHessian::FastHessian(IplImage *img, std::vector<Ipoint> &ipts, 
                         const int octaves, const int intervals, const int init_sample, 
                         const float thresh) 
                         : ipts(ipts), i_width(0), i_height(0)
{
  // Save parameter set
  saveParameters(octaves, intervals, init_sample, thresh);

  // Set the current image
  setIntImage(img);
}

//! Constructor with image
FastHessian::FastHessian(IplImage *img, IplImage *img_orig2, std::vector<Ipoint> &ipts, 
                         const int octaves, const int intervals, const int init_sample, 
                         const float thresh) 
                         : ipts(ipts), i_width(0), i_height(0)
{
  // Save parameter set
  saveParameters(octaves, intervals, init_sample, thresh);
this->img_orig=img_orig2;
  // Set the current image
  setIntImage(img);
}

//-------------------------------------------------------

FastHessian::~FastHessian()
{
  for (unsigned int i = 0; i < responseMap.size(); ++i)
  {
    delete responseMap[i];
  }
}

//-------------------------------------------------------

//! Save the parameters
void FastHessian::saveParameters(const int octaves, const int intervals, 
                                 const int init_sample, const float thresh)
{
  // Initialise variables with bounds-checked values
  this->octaves = 
    (octaves > 0 && octaves <= 4 ? octaves : OCTAVES);
  this->intervals = 
    (intervals > 0 && intervals <= 4 ? intervals : INTERVALS);
  this->init_sample = 
    (init_sample > 0 && init_sample <= 6 ? init_sample : INIT_SAMPLE);
  this->thresh = (thresh >= 0 ? thresh : THRES);
}


//-------------------------------------------------------

//! Set or re-set the integral image source
void FastHessian::setIntImage(IplImage *img)
{
  // Change the source image
  this->img = img;

  i_height = img->height;
  i_width = img->width;
}

//-------------------------------------------------------

//! Find the image features and write into vector of features
void FastHessian::getIpoints()
{
  // filter index map
  static const int filter_map [OCTAVES][INTERVALS] = {{0,1,2,3}, {1,3,4,5}, {3,5,6,7}, {5,7,8,9}, {7,9,10,11}};

  // Clear the vector of exisiting ipts
  ipts.clear();
 clock_t start = clock();
  // Build the response map
  buildResponseMap();
 clock_t end = clock();
 std::cout<< "OpenSURF4 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
  // Get the response layers
  ResponseLayer *b, *m, *t;
  start = clock();

  for (int o = 0; o < octaves; ++o) for (int i = 0; i <= 1; ++i)
  {
    b = responseMap.at(filter_map[o][i]);
    m = responseMap.at(filter_map[o][i+1]);
    t = responseMap.at(filter_map[o][i+2]);

    // loop over middle response layer at density of the most 
    // sparse layer (always top), to find maxima across scale and space

    for (int r = t->height/4; r < t->height-t->height/4; ++r)
    {
      for (int c = t->width/4; c < t->width-t->width/4;++c)
      {
        if (isExtremum(r, c, t, m, b))
        {
          interpolateExtremum(r, c, t, m, b);
        }
      }
    }
  }
 end = clock();std::cout<< "OpenSURF5 took: " <<float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
}
void Test1(IplImage* img_orig, std::vector<ResponseLayer *> responseMap);
//-------------------------------------------------------

//! Build map of DoH responses
void FastHessian::buildResponseMap()
{
  // Calculate responses for the first 4 octaves:
  // Oct1: 9,  15, 21, 27
  // Oct2: 15, 27, 39, 51
  // Oct3: 27, 51, 75, 99
  // Oct4: 51, 99, 147,195
  // Oct5: 99, 195,291,387

  // Deallocate memory and clear any existing response layers
  for(unsigned int i = 0; i < responseMap.size(); ++i)  
    delete responseMap[i];
  responseMap.clear();
std::cout<<"responsemap"<<std::endl;
  // Get image attributes
  int w = (i_width / init_sample);
  int h = (i_height / init_sample);
  int s = (init_sample);

  // Calculate approximated determinant of hessian values
  if (octaves >= 1)
  {
    responseMap.push_back(new ResponseLayer(w,   h,   s,   9));
    responseMap.push_back(new ResponseLayer(w,   h,   s,   15));
    responseMap.push_back(new ResponseLayer(w,   h,   s,   21));
    responseMap.push_back(new ResponseLayer(w,   h,   s,   27));
  }
 
  if (octaves >= 2)
  {
    responseMap.push_back(new ResponseLayer(w/2, h/2, s*2, 39));
    responseMap.push_back(new ResponseLayer(w/2, h/2, s*2, 51));
  }

  if (octaves >= 3)
  {
    responseMap.push_back(new ResponseLayer(w/4, h/4, s*4, 75));
    responseMap.push_back(new ResponseLayer(w/4, h/4, s*4, 99));
  }

  if (octaves >= 4)
  {
    responseMap.push_back(new ResponseLayer(w/8, h/8, s*8, 147));
    responseMap.push_back(new ResponseLayer(w/8, h/8, s*8, 195));
  }

  if (octaves >= 5)
  {
    responseMap.push_back(new ResponseLayer(w/16, h/16, s*16, 291));
    responseMap.push_back(new ResponseLayer(w/16, h/16, s*16, 387));
  }

  // Extract responses from the image
  clock_t start = clock();
  Test1(img,responseMap);
  
  //int filtersize[6] = {9, 15, 21, 27, 39, 51};
  
  //for (unsigned int i = 0; i < responseMap.size(); ++i)
  //{
//	Test1(img_orig, filtersize[i]);
  //}
  
  //cv::Mat hw_inputFrame(img.size(), img.type(), (uchar *) setup_reserved_mem(INPUT_FRAME_ADDR));
  //inFrame.copyTo(hw_inputFrame);
  
  //for (unsigned int i = 0; i < responseMap.size(); ++i)
  //{
  //  buildResponseLayer(responseMap[i]);
  //}//clock_t end = clock();std::cout<< "OpenSURF5 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
  //for (unsigned int i = 0; i < responseMap.size(); ++i)
  //{
  //  buildResponseLayer(responseMap[i]);
  //}//clock_t end = clock();std::cout<< "OpenSURF5 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
}

  #define FILTER_SIZE 9
#define BORDER ((FILTER_SIZE+3)/6)
#define LOBE (FILTER_SIZE/3)
#define DX_TOP (2*LOBE-1)

#define min_1(a, b) ((a < b) ? a : b)

#define MAP_SIZE 4000000UL
#define MAP_MASK (MAP_SIZE - 1)

void * setup_reserved_mem(uint input_address) //returns a pointer in userspace to the device
  {
    void *mapped_base_reserved_mem;
    int memfd_reserved_mem;
    void *mapped_dev_base;
    off_t dev_base = input_address;

    memfd_reserved_mem = open("/dev/mem", O_RDWR | O_SYNC); //to open this the program needs to be run as root
        if (memfd_reserved_mem == -1) {
        printf("Can't open /dev/mem.\n");
        return NULL;
    }
    //printf("/dev/mem opened.\n");

    // Map one page of memory into user space such that the device is in that page, but it may not
    // be at the start of the page.

    mapped_base_reserved_mem = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd_reserved_mem, dev_base & ~MAP_MASK);
        if (mapped_base_reserved_mem == (void *) -1) {
        printf("Can't map the memory to user space.\n");
        return NULL;
    }
     //printf("Memory mapped at address %p.\n", mapped_base_reserved_mem);

    // get the address of the device in user space which will be an offset from the base
    // that was mapped as memory is mapped at the start of a page

    mapped_dev_base = mapped_base_reserved_mem + (dev_base & MAP_MASK);
    return mapped_dev_base;
  }

timespec diff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

float * inputFrame;
int inputFrame_init;
XImage_filter_fh HLSDevice;xVDMA_info_ vdma;xVDMA_info_ vdma2;
int HLSDevice_init;
int xVDMA_init;
float * inframe;
float * outframe[6];
unsigned int inframe_xdma;
unsigned int outframe_xdma[6];
int imgcount;int fd;

void Test1(IplImage* img_orig, std::vector<ResponseLayer *> responseMap)
{
/*char b_[20] = "new/img0000.jpg";
int i=0;
sprintf(b_,"new/img%04i.jpg",imgcount+1);
std::cerr<<"image no "<<imgcount+1<<std::endl;
imgcount++;
cv::Mat inFrame_orig = cv::imread(b_,CV_LOAD_IMAGE_GRAYSCALE);
clock_t start = clock();*/
//cv::Mat inFrame_orig = cv::cvarrToMat(img_orig, true) * 255.0f;
cv::Mat inFrame = cv::cvarrToMat(img_orig);
//   cv::Mat inFrame_orig2 = cv::cvarrToMat(img, true);
  //cv::Mat inFrame(inFrame_orig.size().height+1, inFrame_orig.size().width+1, inFrame_orig.type());
  //cv::Mat inFrame(inFrame_orig.size().height+1, inFrame_orig.size().width+1, inFrame_orig.type());
  //cv::integral(inFrame_orig, inFrame);
/*  cv::Mat inFrame,outFrame;
  inFrame_orig.convertTo(inFrame, CV_8U);
  //inFrame_orig.convertTo(inFrame, CV_32S);
  cv::integral(inFrame, outFrame);
  outFrame.convertTo(inFrame, CV_32F);
  inFrame = inFrame * (1.0/255.0);
  //inFrame_orig.convertTo(inFrame, CV_8U);
  //cv::integral(inFrame, outFrame);
  //outFrame.convertTo(inFrame, CV_32F);
  //inFrame = inFrame * (1.0/255.0);
//inFrame.copyTo(outFrame);
//std::cerr<<inFrame.at<float>(1,1);
//std::cerr<<std::endl;
 // int filtersize[6] = {9, 15, 21, 27, 39, 51};
  
  //cv::Mat inFrame2;
  //cv::Mat outFrame(inFrame.size(), inFrame.type());
  //cv::Mat filter_test(6, 10, CV_32FC1, &filter_x_size_9);
  //inFrame.copyTo(inFrame2);
  //cv::filter2D(inFrame, outFrame, -1, filter_test, cv::Point(4,2));
  *std::ofstream of("filter.txt", std::ofstream::app);
  for(int i=0;i<outFrame.size().height;i++)
  {
	for(int asd=0;asd<outFrame.size().width;asd++)
	{
		of << outFrame.at<float>(i,asd) << " ";
	}
	of << std::endl;
  }
  of.close();*

//inFrame_orig.copyTo(inFrame);
  //inFrame.copyTo(outFrame);
  cv::Rect myROI(0, 0, 640, 480);
  outFrame = inFrame(myROI);
  cv::Mat copy;
  outFrame.copyTo(copy);
  inFrame=copy;
clock_t end = clock();
  std::cout<< "OpenSURF12 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
  */
  
  //#define INPUT_FRAME_ADDR 0x18000000
  #define HLS_ADDR 0x43010000
  
  //VDMA setup parameters
  #define VDMAPixelWidth 4
  #define VDMABaseAddr 0x43C20000
  //#define VDMABaseAddr2 0x43900000
  
  #define XDMA_IOCTL_BASE	'W'
#define XDMA_GET_DEV_INFO	_IO(XDMA_IOCTL_BASE, 1)
#define XDMA_GET_NUM_DEVICES	_IO(XDMA_IOCTL_BASE, 0)
struct timespec time1,time2;
  //if(inputFrame_init == 0)
  //{
//	inputFrame = (float *)setup_reserved_mem(INPUT_FRAME_ADDR);
//	inputFrame_init = 1;
  //}
  
  //cv::Mat hw_inputFrame(inFrame.size(), inFrame.type(), inputFrame);
  //inFrame.copyTo(hw_inputFrame);
  //memcpy(inputFrame, inFrame.data, 640*480*4);
  //std::cerr<<hw_inputFrame.at<float>(1,1)<<std::endl;
  //int fd;
  if(HLSDevice_init == 0)
  {
	HLSDevice_init = 1;
	HLSDevice = setup_ximage_filter_fh(HLS_ADDR);
	
	fd = open("/dev/xdma", O_RDWR);	
	if (fd < 1) {
			printf("Unable to open DMA proxy device file");
			return;
		}
	int bufi=0;
	ioctl(fd, XDMA_GET_DEV_INFO, &bufi);
	inframe = (float*)mmap(NULL, 1250000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	ioctl(fd, XDMA_GET_NUM_DEVICES, &inframe_xdma);
	
	for(int i=0;i<6;i++)
	{
	bufi=i+1;
	ioctl(fd, XDMA_GET_DEV_INFO, &bufi);
	outframe[i] = (float*)mmap(NULL, 1250000, 
										PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x400000*(i+1));
	ioctl(fd, XDMA_GET_NUM_DEVICES, &outframe_xdma[i]);
	}
	//close(fd);
  }

  cv::Mat hw_inputFrame(inFrame.size(), inFrame.type(), inframe);
  //inFrame.copyTo(hw_inputFrame);
clock_gettime(CLOCK_REALTIME, &time1);
//int bufi_=9;
//ioctl(fd, XDMA_GET_DEV_INFO, &bufi_);
  memcpy(inframe, inFrame.data, 640*480*4);
int bufi=0;
ioctl(fd, XDMA_GET_DEV_INFO, &bufi);
  //std::cerr<<hw_inputFrame.at<float>(1,1)<<std::endl;
clock_gettime(CLOCK_REALTIME, &time2);
std::cout << "asd" << diff(time1, time2).tv_sec << ":" << diff(time1, time2).tv_nsec << std::endl;
  
   XImage_filter_fh_Set_rows(&HLSDevice, inFrame.rows);
   XImage_filter_fh_Set_cols(&HLSDevice, inFrame.cols);
   XImage_filter_fh_Set_filter_size(&HLSDevice,21);
   //*(volatile unsigned int*)(HLSDevice.Control_bus_BaseAddress+0x28) = 1;
   //unsigned int tmpdofilter = XImage_filter_Get_do_filter(&HLSDevice);
   //XImage_filter_Set_do_filter(&HLSDevice,0x1);
   //XImage_filter_Set_rows2(&HLSDevice, inFrame.rows);
   //XImage_filter_Set_cols2(&HLSDevice, inFrame.cols);
//XImage_filter_Set_filter_mode(&HLSDevice,0);
   //int filtersize = XImage_filter_Get_filter_size(&HLSDevice);
   int filtersize;
   //std::cerr<<filtersize<<std::endl;
  if(xVDMA_init == 0)
  {
    xVDMA_init = 1;
	xVDMA_Init_(&vdma, VDMABaseAddr, inFrame.cols, inFrame.rows, VDMAPixelWidth);
//xVDMA_Init(&vdma2, VDMABaseAddr2, inFrame.cols, inFrame.rows, VDMAPixelWidth);  
}
int filtersizes[6];
filtersizes[0]=9;
filtersizes[1]=15;
filtersizes[2]=21;
filtersizes[3]=27;
filtersizes[4]=39;
filtersizes[5]=51;
for(int i=0;i<6;i++)
{
	//std::cerr<<"test"<<" "<<inFrame.at<float>(0,1)<<std::endl;
	//while(!XImage_filter_fh_IsReady(&HLSDevice)){}
	//std::cerr<<"test2"<<std::endl;
	clock_gettime(CLOCK_REALTIME, &time1);
	XImage_filter_fh_Set_filter_size(&HLSDevice,filtersizes[i]);
 
	//std::cerr<<std::setbase(16)<<outframe_xdma[i]<<std::endl;
	//std::cerr<<std::setbase(16)<<outframe[i]<<std::endl;
	cv::Mat hw_outputFrame(480, 640, CV_32FC1, outframe[i]);
	//std::cerr<<std::setbase(16)<<inframe_2p<<std::endl;
	//std::cerr<<std::setbase(16)<<inframe2<<std::endl;
	//cv::Mat hw_outputFrame2(480, 640, CV_32FC1, inframe2);
	//memset(outframe[i],0,480*640*4);
	//std::cerr<<outframe[i][0]<<std::endl;
	
	//memset(hw_outputFrame2.data,0,480*640*4);
clock_gettime(CLOCK_REALTIME, &time1);

        	XImage_filter_fh_Start(&HLSDevice); //Kick it to start it
//        	xVDMA_kick(&vdma2, inframe_xdma, inframe_xdma);
		xVDMA_kick_(&vdma, inframe_xdma, outframe_xdma[i]);
	//	while(!XImage_filter_fh_IsReady(&HLSDevice) || xVDMA_IsRunning_(&vdma)){}
//std::cerr<<"test3"<<std::endl;
 		bufi=i+1;
		ioctl(fd, XDMA_GET_DEV_INFO, &bufi);

        clock_gettime(CLOCK_REALTIME, &time2);std::cerr<<outframe[i][641]<<std::endl;

        std::cout << diff(time1, time2).tv_sec << ":" << diff(time1, time2).tv_nsec << std::endl;
	//std::cout << outframe[i][4*640+8] << std::endl;
	//bufi=i+1;
	//ioctl(fd, XDMA_GET_DEV_INFO, &bufi);
	(*responseMap[i]).responses = outframe[i];
/*
while(!XImage_filter_IsReady(&HLSDevice)){}
//inFrame = inFrame * 0.5f;
	 memcpy(inputFrame, inFrame.data, 640*480*4);
XImage_filter_Set_filter_size(&HLSDevice,9);
filtersize = XImage_filter_Get_filter_size(&HLSDevice);
std::cerr<<filtersize<<std::endl;
while(!XImage_filter_IsReady(&HLSDevice)){}
memset(inframe,0,480*640*4);
	std::cerr<<inframe[0]<<std::endl;

XImage_filter_Start(&HLSDevice); //Kick it to start it
        	xVDMA_kick(&vdma, INPUT_FRAME_ADDR, inframe_p);
		while(!XImage_filter_IsDone(&HLSDevice) || xVDMA_IsRunning(&vdma)){}

std::cerr<<inframe[0]<<std::endl;
//std::cerr<<inframe2[0]<<std::endl;
        //cv::Mat tempFrame(480,640,CV_32FC1);float *tmp = new float[480*640*50];              float *tmp2 = new float[480*640*50];
	
	clock_gettime(CLOCK_REALTIME, &time2);
	//memcpy(tempFrame.data, hw_outputFrame.data, 480*640*4);
        //hw_outputFrame.copyTo(tempFrame);
	memcpy(inframe, inframe2, 480*640*4);
	clock_gettime(CLOCK_REALTIME, &time1);*/
//munmap(inframe,3500000);

	/*std::cout << diff(time2, time1).tv_sec << ":" << diff(time2, time1).tv_nsec << std::endl;
std::ofstream of2("filter2.txt", std::ofstream::app);
  for(int i=0;i<480;i++)
  {
	for(int asd=0;asd<640;asd++)
	{
		of2 << hw_outputFrame.at<float>(i,asd) << " ";
	}
	of2 << std::endl;
  }
  of2.close();*/
}/*
of2.open("filter2_.txt", std::ofstream::app);
  for(int i=0;i<480;i++)
  {
	for(int asd=0;asd<640;asd++)
	{
		of2 << hw_outputFrame2.at<float>(i,asd) << " ";
	}
	of2 << std::endl;
  }
  of2.close();*/
//munmap(inframe,3500000);
//munmap(inframe2,3500000);

  /*
  float * OUTPUT_FRAME_ADDR[6] = {(float*)0x19000000,(float*)0x19400000,(float*)0x19800000,(float*)0x19C00000,(float*)0x1A000000,(float*)0x1A400000};
   
  for(int i=0;i<6;i++)
	{
if(i>0)	while(!XImage_filter_IsReady(&HLSDevice)){}
std::cerr<<"test2"<<std::endl;
clock_gettime(CLOCK_REALTIME, &time1);
XImage_filter_SetFilter_size(&HLSDevice,filtersize[i]);
	    	XImage_filter_Start(&HLSDevice); //Kick it to start it
        	xVDMA_kick(&vdma, INPUT_FRAME_ADDR, (unsigned int)OUTPUT_FRAME_ADDR[i]);
		while(!XImage_filter_IsDone(&HLSDevice) || xVDMA_IsRunning(&vdma)){}
std::cerr<<"test3"<<std::endl;
        clock_gettime(CLOCK_REALTIME, &time2);

        std::cout << diff(time1, time2).tv_sec << ":" << diff(time1, time2).tv_nsec << std::endl;

        //cv::Mat outFrame;
	//clock_gettime(CLOCK_REALTIME, &time2);
        //hw_outputFrame.copyTo(outFrame);
	//clock_gettime(CLOCK_REALTIME, &time1);
	cv::Mat hw_outputFrame(inFrame_orig.size(), inFrame_orig.type(), (*responseMap[i]).responses);
	std::cerr<<(*responseMap[i]).responses[0*640+2]<<std::endl;
	std::cout << diff(time2, time1).tv_sec << ":" << diff(time2, time1).tv_nsec << std::endl;

	std::ofstream of2("filter2.txt", std::ofstream::app);
  for(int i=0;i<480;i++)
  {
	for(int asd=0;asd<640;asd++)
	{
		of2 << hw_outputFrame.at<float>(i,asd) << " ";
	}
	of2 << std::endl;
  }
  of2.close();
	//outFrame.convertTo(outFrame, CV_8UC1);
//        imshow("output", outFrame);
//		cv::waitKey(10);
	
	


}*/
	
  //inFrame.copyTo(outFrame);
  //inFrame_orig.copyTo(outFrame);
  
  /*int IMG_HEIGHT=outFrame.size().height+FILTER_SIZE;
  int IMG_WIDTH=outFrame.size().width+FILTER_SIZE;
  
  float *input = new float[IMG_WIDTH*IMG_HEIGHT];
  float *buffer = new float[(FILTER_SIZE+1)*IMG_WIDTH];
  float *output = new float[IMG_WIDTH*IMG_HEIGHT];
  const float inverse_area = 1.f/(FILTER_SIZE*FILTER_SIZE);
	const int b = (FILTER_SIZE - 1) / 2;             // border for this filter
	const int l = (FILTER_SIZE / 3);                   // lobe for this filter (filter size / 3)
	const int w = FILTER_SIZE;                       // filter size
  for(int i=0;i<IMG_HEIGHT;i++)
  {
	for(int asd=0;asd<IMG_WIDTH;asd++)
	{
		if(i<outFrame.size().height)
		if(asd<outFrame.size().width)
			input[i*(IMG_WIDTH)+asd]=outFrame.at<float>(i,asd);//temp[i*outFrame.size().width+asd];
		else
			input[i*(IMG_WIDTH)+asd]=outFrame.at<float>(i,outFrame.size().width-1);//[i*outFrame.size().width+outFrame.size().width-1];
		else
		if(asd<outFrame.size().width)
			input[i*IMG_WIDTH+asd]=outFrame.at<float>(outFrame.size().height-1,asd);//temp[(outFrame.size().heigh-1)*outFrame.size().width+asd];
		else
			input[i*IMG_WIDTH+asd]=outFrame.at<float>(outFrame.size().height-1, outFrame.size().width-1);//temp[(outFrame.size().heigh-1)*outFrame.size().width+outFrame.size().width-1];
	}
	}
	
	for(int count=0;count<((FILTER_SIZE+1)/2)*IMG_WIDTH+((FILTER_SIZE+1)/2);count++)
	{
		// unroll this
		for(int i = (FILTER_SIZE+1)*IMG_WIDTH - 1; i > 0; i--)
		{
			 buffer[i] = buffer[i-1];
		}
		
		//input >> buffer[0];
		buffer[0] = input[count];
	}
	
	std::cerr<<" "<<outFrame.at<float>(0,1)<<std::endl;
	
	int r=0;
	int c=0;
	for(int count=0;count<IMG_HEIGHT*IMG_WIDTH;count++)
	{
		// unroll this
		for(int i = (FILTER_SIZE+1)*IMG_WIDTH - 1; i > 0; i--)
		{
			 buffer[i] = buffer[i-1];
		}
		
		if(count<IMG_HEIGHT*IMG_WIDTH-(((FILTER_SIZE+1)/2)*IMG_WIDTH+(FILTER_SIZE+1)/2))
			//input >> buffer[0];
			buffer[0] = input[count+((FILTER_SIZE+1)/2)*IMG_WIDTH+((FILTER_SIZE+1)/2)];
		else
			buffer[0]=0;
			
		//if(count==0)
		//	std::cerr<<buffer[0];
			
		float A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Z1, Z2, Z3, Z4, Z5, Z6;
		A=0.0f;
		B=0.0f;
		C=0.0f;
		D=0.0f;
		E=0.0f;
		F=0.0f;
		G=0.0f;
		H=0.0f;
		I=0.0f;
		J=0.0f;
		K=0.0f;
		L=0.0f;
		M=0.0f;
		N=0.0f;
		O=0.0f;
		P=0.0f;
		Q=0.0f;
		R=0.0f;
		S=0.0f;
		T=0.0f;
		U=0.0f;
		V=0.0f;
		W=0.0f;
		X=0.0f;
		Y=0.0f;
		Z=0.0f;
		Z1=0.0f;
		Z2=0.0f;
		Z3=0.0f;
		Z4=0.0f;
		Z5=0.0f;
		Z6=0.0f;
		
		int row_1 = r - l + 1;
		int col_1 = c - b;
		int row_2 = r + l;
		int col_2 = c - b + w;
		int col_3 = c - l/2;
		int col_4 = c - l/2 + l;
		int row_3 = r - b;
		int col_5 = c - l + 1;
		int row_4 = r - b + w;
		int col_6 = c + l;
		int row_5 = r - l / 2;
		int row_6 = r - l / 2 + l;
		int row_7 = r - l;
		int col_7 = c + 1;
		int row_8 = r;
		int col_8 = c + 1 + l;
		int row_9 = r + 1;
		int col_9 = c - l;
		int row_10 = r + 1 + l;
		int col_10 = c;
		
		int r1 = min_1(row_1,          IMG_HEIGHT) - 1;
		int c1 = min_1(col_1,          IMG_WIDTH)  - 1;
		int r2 = min_1(row_2,   IMG_HEIGHT) - 1;
		int c2 = min_1(col_2,   IMG_WIDTH)  - 1;
		int r3 = min_1(row_3,          IMG_HEIGHT) - 1;
		int c3 = min_1(col_3,          IMG_WIDTH)  - 1;
		int r4 = min_1(row_4,   IMG_HEIGHT) - 1;
		int c4 = min_1(col_4,   IMG_WIDTH)  - 1;
		int r5 = min_1(row_5,          IMG_HEIGHT) - 1;
		int c5 = min_1(col_5,          IMG_WIDTH)  - 1;
		int r6 = min_1(row_6,   IMG_HEIGHT) - 1;
		int c6 = min_1(col_6,   IMG_WIDTH)  - 1;
		int r7 = min_1(row_7,          IMG_HEIGHT) - 1;
		int c7 = min_1(col_7,          IMG_WIDTH)  - 1;
		int r8 = min_1(row_8,   IMG_HEIGHT) - 1;
		int c8 = min_1(col_8,   IMG_WIDTH)  - 1;
		int r9 = min_1(row_9,          IMG_HEIGHT) - 1;
		int c9 = min_1(col_9,          IMG_WIDTH)  - 1;
		int r10 = min_1(row_10,   IMG_HEIGHT) - 1;int c10 = min_1(col_10,   IMG_WIDTH) - 1;
		
		if (r1 >= 0 && c1 >= 0) A = buffer[DX_TOP*IMG_WIDTH+FILTER_SIZE+BORDER*IMG_WIDTH];
		if (r1 >= 0 && c2 >= 0) B = buffer[DX_TOP*IMG_WIDTH+BORDER*IMG_WIDTH];
		if (r2 >= 0 && c1 >= 0) C = buffer[FILTER_SIZE+BORDER*IMG_WIDTH];
		if (r2 >= 0 && c2 >= 0) D = buffer[0+BORDER*IMG_WIDTH];

		if (r1 >= 0 && c3 >= 0) E = buffer[DX_TOP*IMG_WIDTH+(FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH];
		if (r1 >= 0 && c4 >= 0) F = buffer[DX_TOP*IMG_WIDTH+LOBE+BORDER*IMG_WIDTH];
		if (r2 >= 0 && c3 >= 0) G = buffer[(FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH];
		if (r2 >= 0 && c4 >= 0) H = buffer[LOBE+BORDER*IMG_WIDTH];

		if (r3 >= 0 && c5 >= 0) I = buffer[FILTER_SIZE*IMG_WIDTH+(FILTER_SIZE-BORDER)];
		if (r3 >= 0 && c6 >= 0) J = buffer[FILTER_SIZE*IMG_WIDTH+BORDER];
		if (r4 >= 0 && c5 >= 0) K = buffer[FILTER_SIZE-BORDER];
		if (r4 >= 0 && c6 >= 0) L = buffer[BORDER];

		if (r5 >= 0 && c5 >= 0) M = buffer[(FILTER_SIZE-LOBE)*IMG_WIDTH+(FILTER_SIZE-BORDER)];
		if (r5 >= 0 && c6 >= 0) N = buffer[(FILTER_SIZE-LOBE)*IMG_WIDTH+BORDER];
		if (r6 >= 0 && c5 >= 0) O = buffer[LOBE*IMG_WIDTH+(FILTER_SIZE-BORDER)];
		if (r6 >= 0 && c6 >= 0) P = buffer[LOBE*IMG_WIDTH+BORDER];

		if (r7 >= 0 && c7 >= 0) Q = buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1+LOBE];
		if (r7 >= 0 && c8 >= 0) R = buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1];
		if (r8 >= 0 && c7 >= 0) S = buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1+LOBE];
		if (r8 >= 0 && c8 >= 0) T = buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1];

		if (r9 >= 0 && c9 >= 0) U = buffer[(BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))];
		if (r9 >= 0 && c10 >= 0) V = buffer[(BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)];
		if (r10 >= 0 && c9 >= 0) W = buffer[(BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))];
		if (r10 >= 0 && c10 >= 0) X = buffer[(BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)];

		if (r7 >= 0 && c9 >= 0) Y = buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))];
		if (r7 >= 0 && c10 >= 0) Z = buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)];
		if (r8 >= 0 && c9 >= 0) Z1 = buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))];
		if (r8 >= 0 && c10 >= 0) Z2 = buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)];

		if (r9 >= 0 && c7 >= 0) Z3 = buffer[(LOBE+BORDER-1)*IMG_WIDTH+BORDER-1+LOBE];
		if (r9 >= 0 && c8 >= 0) Z4 = buffer[(LOBE+BORDER-1)*IMG_WIDTH+BORDER-1];
		if (r10 >= 0 && c7 >= 0) Z5 = buffer[(BORDER-1)*IMG_WIDTH+BORDER-1+LOBE];
		if (r10 >= 0 && c8 >= 0) Z6 = buffer[(BORDER-1)*IMG_WIDTH+BORDER-1];
		
		//float Dxx_9 = buffer[0+BORDER*IMG_WIDTH] - buffer[FILTER_SIZE+BORDER*IMG_WIDTH] - buffer[DX_TOP*IMG_WIDTH+BORDER*IMG_WIDTH] + buffer[DX_TOP*IMG_WIDTH+FILTER_SIZE+BORDER*IMG_WIDTH] - 3*buffer[LOBE+BORDER*IMG_WIDTH] + 3*buffer[(FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH] + 3*buffer[DX_TOP*IMG_WIDTH+LOBE+BORDER*IMG_WIDTH] - 3*buffer[DX_TOP*IMG_WIDTH+(FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH];
		//float Dyy_9 = buffer[BORDER] - buffer[FILTER_SIZE-BORDER] - buffer[FILTER_SIZE*IMG_WIDTH+BORDER] + buffer[FILTER_SIZE*IMG_WIDTH+(FILTER_SIZE-BORDER)] - 3*buffer[LOBE*IMG_WIDTH+BORDER] + 3*buffer[LOBE*IMG_WIDTH+(FILTER_SIZE-BORDER)] + 3*buffer[(FILTER_SIZE-LOBE-1)*IMG_WIDTH+BORDER] - 3*buffer[(FILTER_SIZE-LOBE-1)*IMG_WIDTH+(FILTER_SIZE-BORDER)];
		//float Dxy_9 = - buffer[(BORDER-1)*IMG_WIDTH+BORDER-1] + buffer[(BORDER-1)*IMG_WIDTH+BORDER-1+LOBE] + buffer[(LOBE+BORDER-1)*IMG_WIDTH+BORDER-1] - buffer[(LOBE+BORDER-1)*IMG_WIDTH+BORDER-1+LOBE] + buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1] - buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1+LOBE] - buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1] + buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1+LOBE]
		//				+ buffer[(BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] - buffer[(BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))] - buffer[(BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] + buffer[(BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))] - buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] + buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))] + buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] - buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))];

		
		float Dxx_9 = A - B - C + D - (E - F - G + H)*3;
		//if(r==2&&c==4)std::cerr<<"dxx"<<Dxx_9<<std::endl;
		float Dyy_9 = I - J - K + L - (M - N - O + P)*3;
		//if(r==2&&c==4)std::cerr<<"Dyy_9 "<<Dyy_9<<std::endl;
		float Dxy_9 = (Q - R - S + T) + (U - V - W + X) - (Y - Z - Z1 + Z2) - (Z3 - Z4 - Z5 + Z6);
		//if(r==2&&c==4)std::cerr<<"Dxy_9 "<<Dxy_9<<std::endl;
		Dxx_9 *= inverse_area;
		Dyy_9 *= inverse_area;
		Dxy_9 *= inverse_area;
		
		//output << (Dxx_9 * Dyy_9 - 0.81f * Dxy_9 * Dxy_9);
		output[count] = Dxx_9 * Dyy_9 - 0.81f * Dxy_9 * Dxy_9;
		
		//if(r==2&&c==4)std::cerr<<count<<" "<<c<<" "<<r<<" "<<M<<" "<<N<<" "<<O<<" "<<P<<std::endl;
		
		if(c<IMG_WIDTH-1)
			c++;
		else
		{
			c=0;
			r++;
		}
	}
	
	std::ofstream of2("filter2.txt", std::ofstream::app);
  for(int i=0;i<IMG_HEIGHT;i++)
  {
	for(int asd=0;asd<IMG_WIDTH;asd++)
	{
		of2 << output[i*IMG_WIDTH+asd] << " ";
	}
	of2 << std::endl;
  }
  of2.close();*/}

void SetFilter(float* filter, int widthStep, int row, int col, float val)
{
	filter[row*widthStep+col]=val;
}

void MakeDxx(int filtersize, float* filter)
{
	int lobe = filtersize/3;
	int width = filtersize+1; //anchor width/2-1
	int height = 2*lobe; //anchor height/2-1
	
	filter = new float[width*height];
	SetFilter(filter, width, 0, 0, 1.0f);
	SetFilter(filter, width, 0, width-1, -1.0f);
	SetFilter(filter, width, height-1, 0, -1.0f);
	SetFilter(filter, width, height-1, width-1, 1.0f);
	
	SetFilter(filter, width, 0, lobe, -3.0f);
	SetFilter(filter, width, 0, width-1-lobe, 3.0f);
	SetFilter(filter, width, height-1, lobe, 3.0f);
	SetFilter(filter, width, height-1, width-1-lobe, -3.0f);
}

void MakeDyy(int filtersize, float* filter)
{
	int lobe = filtersize/3;
	int height = filtersize+1; //anchor height/2-1
	int width = 2*lobe; //anchor width/2-1
	
	filter = new float[width*height];
	SetFilter(filter, width, 0, 0, 1.0f);
	SetFilter(filter, width, 0, width-1, -1.0f);
	SetFilter(filter, width, height-1, 0, -1.0f);
	SetFilter(filter, width, height-1, width-1, 1.0f);
	
	SetFilter(filter, width, lobe, 0, -3.0f);
	SetFilter(filter, width, lobe, width-1, 3.0f);
	SetFilter(filter, width, height-1-lobe, 0, 3.0f);
	SetFilter(filter, width, height-1-lobe, width-1, -3.0f);
}

void MakeDxy(int filtersize, float* filter)
{
	int lobe = filtersize/3;
	int height = 2*lobe+2; //anchor height/2-1
	int width = 2*lobe+2; //anchor width/2-1
	
	filter = new float[width*height];
	SetFilter(filter, width, 0, 0, -1.0f); //r-l, c+1, l, l
	SetFilter(filter, width, 0, lobe, 1.0f);
	SetFilter(filter, width, lobe, 0, 1.0f);
	SetFilter(filter, width, lobe, lobe, -1.0f);
	
	SetFilter(filter, width, 0, width-1-lobe, 1.0f); //r-l, c+1, l, l
	SetFilter(filter, width, 0, width-1, -1.0f);
	SetFilter(filter, width, lobe, width-1-lobe, -1.0f);
	SetFilter(filter, width, lobe, width-1, 1.0f);
	
	SetFilter(filter, width, height-1-lobe, 0, 1.0f); //r-l, c+1, l, l
	SetFilter(filter, width, height-1-lobe, lobe, -1.0f);
	SetFilter(filter, width, height-1, 0, -1.0f);
	SetFilter(filter, width, height-1, lobe, 1.0f);
	
	SetFilter(filter, width, height-1-lobe, width-1-lobe, -1.0f); //r-l, c+1, l, l
	SetFilter(filter, width, height-1-lobe, width-1, 1.0f);
	SetFilter(filter, width, height-1, width-1-lobe, 1.0f);
	SetFilter(filter, width, height-1, width-1, -1.0f);
}
	
//-------------------------------------------------------

//! Calculate DoH responses for supplied layer
void FastHessian::buildResponseLayer(ResponseLayer *rl)
{
  float *responses = rl->responses;         // response storage
  unsigned char *laplacian = rl->laplacian; // laplacian sign storage
  int step = rl->step;                      // step size for this filter
  int b = (rl->filter - 1) / 2;             // border for this filter
  int l = rl->filter / 3;                   // lobe for this filter (filter size / 3)
  int w = rl->filter;                       // filter size
  float inverse_area = 1.f/(w*w);           // normalisation factor
  float Dxx, Dyy, Dxy;

  clock_t a=0;
  for(int r, c, ar = 0, index = 0; ar < rl->height; ++ar) 
  {
    for(int ac = 0; ac < rl->width; ++ac, index++) 
    {
      // get the image coordinates
      r = ar * step;
      c = ac * step; 
		clock_t start = clock();
		 
	int row_1 = r - l + 1;
	int col_1 = c - b;
	int row_2 = r + l;
	int col_2 = c - b + w;
	int col_3 = c - l/2;
	int col_4 = c - l/2 + l;
	int row_3 = r - b;
	int col_5 = c - l + 1;
	int row_4 = r - b + w;
	int col_6 = c + l;
	int row_5 = r - l / 2;
	int row_6 = r - l / 2 + l;
	int row_7 = r - l;
	int col_7 = c + 1;
	int row_8 = r;
	int col_8 = c + 1 + l;
	int row_9 = r + 1;
	int col_9 = c - l;
	int row_10 = r + 1 + l;
	int col_10 = c;
	
	float *data = (float *) img->imageData;
	int step2 = img->widthStep/sizeof(float);

  // The subtraction by one for row/col is because row/col is inclusive.
  int r1 = std::min(row_1,          img->height) - 1;
  int c1 = std::min(col_1,          img->width)  - 1;
  int r2 = std::min(row_2,   img->height) - 1;
  int c2 = std::min(col_2,   img->width)  - 1;
  int r3 = std::min(row_3,          img->height) - 1;
  int c3 = std::min(col_3,          img->width)  - 1;
  int r4 = std::min(row_4,   img->height) - 1;
  int c4 = std::min(col_4,   img->width)  - 1;
  int r5 = std::min(row_5,          img->height) - 1;
  int c5 = std::min(col_5,          img->width)  - 1;
  int r6 = std::min(row_6,   img->height) - 1;
  int c6 = std::min(col_6,   img->width)  - 1;
  int r7 = std::min(row_7,          img->height) - 1;
  int c7 = std::min(col_7,          img->width)  - 1;
  int r8 = std::min(row_8,   img->height) - 1;
  int c8 = std::min(col_8,   img->width)  - 1;
  int r9 = std::min(row_9,          img->height) - 1;
  int c9 = std::min(col_9,          img->width)  - 1;
  int r10 = std::min(row_10,   img->height) - 1;int c10 = std::min(col_10,   img->width) - 1;
  //int c2 = std::min(col_2,   img->width)  - 1;


  //float A(0.0f), B(0.0f), C(0.0f), D(0.0f);
  float A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Z1, Z2, Z3, Z4, Z5, Z6;
  A=0.0f;
  B=0.0f;
  C=0.0f;
  D=0.0f;
  E=0.0f;
  F=0.0f;
  G=0.0f;
  H=0.0f;
  I=0.0f;
  J=0.0f;
  K=0.0f;
  L=0.0f;
  M=0.0f;
  N=0.0f;
  O=0.0f;
  P=0.0f;
  Q=0.0f;
  R=0.0f;
  S=0.0f;
  T=0.0f;
  U=0.0f;
  V=0.0f;
  W=0.0f;
  X=0.0f;
  Y=0.0f;
  Z=0.0f;
  Z1=0.0f;
  Z2=0.0f;
  Z3=0.0f;
  Z4=0.0f;
  Z5=0.0f;
  Z6=0.0f;
  if (r1 >= 0 && c1 >= 0) A = data[r1 * step2 + c1];
  if (r1 >= 0 && c2 >= 0) B = data[r1 * step2 + c2];
  if (r2 >= 0 && c1 >= 0) C = data[r2 * step2 + c1];
  if (r2 >= 0 && c2 >= 0) D = data[r2 * step2 + c2];
  
  if (r1 >= 0 && c3 >= 0) E = data[r1 * step2 + c3];
  if (r1 >= 0 && c4 >= 0) F = data[r1 * step2 + c4];
  if (r2 >= 0 && c3 >= 0) G = data[r2 * step2 + c3];
  if (r2 >= 0 && c4 >= 0) H = data[r2 * step2 + c4];
  
  if (r3 >= 0 && c5 >= 0) I = data[r3 * step2 + c5];
  if (r3 >= 0 && c6 >= 0) J = data[r3 * step2 + c6];
  if (r4 >= 0 && c5 >= 0) K = data[r4 * step2 + c5];
  if (r4 >= 0 && c6 >= 0) L = data[r4 * step2 + c6];
  
  if (r5 >= 0 && c5 >= 0) M = data[r5 * step2 + c5];
  if (r5 >= 0 && c6 >= 0) N = data[r5 * step2 + c6];
  if (r6 >= 0 && c5 >= 0) O = data[r6 * step2 + c5];
  if (r6 >= 0 && c6 >= 0) P = data[r6 * step2 + c6];
  
  
  if (r7 >= 0 && c7 >= 0) Q = data[r7 * step2 + c7];
  if (r7 >= 0 && c8 >= 0) R = data[r7 * step2 + c8];
  if (r8 >= 0 && c7 >= 0) S = data[r8 * step2 + c7];
  if (r8 >= 0 && c8 >= 0) T = data[r8 * step2 + c8];
  
   if (r9 >= 0 && c9 >= 0) U = data[r9 * step2 + c9];
  if (r9 >= 0 && c10 >= 0) V = data[r9 * step2 + c10];
  if (r10 >= 0 && c9 >= 0) W = data[r10 * step2 + c9];
  if (r10 >= 0 && c10 >= 0) X = data[r10 * step2 + c10];
  
   if (r7 >= 0 && c9 >= 0) Y = data[r7 * step2 + c9];
  if (r7 >= 0 && c10 >= 0) Z = data[r7 * step2 + c10];
  if (r8 >= 0 && c9 >= 0) Z1 = data[r8 * step2 + c9];
  if (r8 >= 0 && c10 >= 0) Z2 = data[r8 * step2 + c10];
  
   if (r9 >= 0 && c7 >= 0) Z3 = data[r9 * step2 + c7];
  if (r9 >= 0 && c8 >= 0) Z4 = data[r9 * step2 + c8];
  if (r10 >= 0 && c7 >= 0) Z5 = data[r10 * step2 + c7];
  if (r10 >= 0 && c8 >= 0) Z6 = data[r10 * step2 + c8];

  //return std::max(0.f, A - B - C + D);
	

      // Compute response components
      //Dxx = BoxIntegral(img, r - l + 1, c - b, 2*l - 1, w)
     //    - BoxIntegral(img, r - l + 1, c - l / 2, 2*l - 1, l)*3;
		  
	  Dxx = std::max(0.f, A - B - C + D) - std::max(0.f, E - F - G + H)*3;
	  
		
	  Dyy = std::max(0.f, I - J - K + L) - std::max(0.f, M - N - O + P)*3;/*;if(ar==1&&ac==2)
		//std::cerr<<Dyy<<std::endl;*/
		//if(ar==1&&ac==2)std::cerr<<"asd"<<" "<<c<<" "<<r<<" "<<M<<" "<<N<<" "<<O<<" "<<P<<std::endl;
	  Dxy = std::max(0.f, Q - R - S + T) + std::max(0.f, U - V - W + X) - std::max(0.f, Y - Z - Z1 + Z2) - std::max(0.f, Z3 - Z4 - Z5 + Z6);
		  //if(ar==1&&ac==2)
		  //std::cerr<<Dxx * Dyy - 0.81f * Dxy * Dxy<<std::endl;
		 
		/*  
      Dyy = BoxIntegral(img, r - b, c - l + 1, w, 2*l - 1)
          - BoxIntegral(img, r - l / 2, c - l + 1, l, 2*l - 1)*3;
      Dxy = + BoxIntegral(img, r - l, c + 1, l, l)
            + BoxIntegral(img, r + 1, c - l, l, l)
            - BoxIntegral(img, r - l, c - l, l, l)
            - BoxIntegral(img, r + 1, c + 1, l, l);*/
			clock_t end = clock();
		a+=end-start;
      // Normalise the filter responses with respect to their size
      Dxx *= inverse_area;
      Dyy *= inverse_area;
      Dxy *= inverse_area;if(ar==1&&ac==2)std::cerr<<Dxx * Dyy - 0.81f * Dxy * Dxy<<std::endl;
     
      // Get the determinant of hessian response & laplacian sign
      responses[index] = (Dxx * Dyy - 0.81f * Dxy * Dxy);
      laplacian[index] = (Dxx + Dyy >= 0 ? 1 : 0);

#ifdef RL_DEBUG
      // create list of the image coords for each response
      rl->coords.push_back(std::make_pair<int,int>(r,c));
#endif
    }
  }//std::cout<< "OpenSURF6 took: " << float(a) / CLOCKS_PER_SEC  << " seconds" << std::endl;
}
  
//-------------------------------------------------------

//! Non Maximal Suppression function
int FastHessian::isExtremum(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b)
{
  // bounds check
  int layerBorder = (t->filter + 1) / (2 * t->step);
  if (r <= layerBorder || r >= t->height - layerBorder || c <= layerBorder || c >= t->width - layerBorder)
    return 0;

  // check the candidate point in the middle layer is above thresh 
  float candidate = m->getResponse(r, c, t);
  if (candidate < thresh) 
    return 0; 

  for (int rr = -1; rr <=1; ++rr)
  {
    for (int cc = -1; cc <=1; ++cc)
    {
      // if any response in 3x3x3 is greater candidate not maximum
      if (
        t->getResponse(r+rr, c+cc) >= candidate ||
        ((rr != 0 || cc != 0) && m->getResponse(r+rr, c+cc, t) >= candidate) ||
        b->getResponse(r+rr, c+cc, t) >= candidate
        ) 
        return 0;
    }
  }

  return 1;
}

//-------------------------------------------------------

//! Interpolate scale-space extrema to subpixel accuracy to form an image feature.   
void FastHessian::interpolateExtremum(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b)
{
  // get the step distance between filters
  // check the middle filter is mid way between top and bottom
  int filterStep = (m->filter - b->filter);
  assert(filterStep > 0 && t->filter - m->filter == m->filter - b->filter);
 
  // Get the offsets to the actual location of the extremum
  double xi = 0, xr = 0, xc = 0;
  interpolateStep(r, c, t, m, b, &xi, &xr, &xc );

  // If point is sufficiently close to the actual extremum
  if( fabs( xi ) < 0.5f  &&  fabs( xr ) < 0.5f  &&  fabs( xc ) < 0.5f )
  {
    Ipoint ipt;
    ipt.x = static_cast<float>((c + xc) * t->step);
    ipt.y = static_cast<float>((r + xr) * t->step);
    ipt.scale = static_cast<float>((0.1333f) * (m->filter + xi * filterStep));
    ipt.laplacian = static_cast<int>(m->getLaplacian(r,c,t));
    ipts.push_back(ipt);
  }
}

//-------------------------------------------------------

//! Performs one step of extremum interpolation. 
void FastHessian::interpolateStep(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b, 
                                  double* xi, double* xr, double* xc )
{
//#ifndef USEOPENCV
  CvMat2* dD, * H, * H_inv, *X;
  double x[3] = { 0 };
  
  double H_[3][3], H_inv_[3][3], dD_ [3][1], X_[3][1];

  dD = deriv3D( r, c, t, m, b );
  dD_[0][0] = dD->data.db[0];
  dD_[1][0] = dD->data.db[1];
  dD_[2][0] = dD->data.db[2];
  H = hessian3D( r, c, t, m, b );
  //H_inv = cvCreateMat( 3, 3, CV_64FC1 );
  H_[0][0] = H->data.db[0];
  H_[0][1] = H->data.db[1];
  H_[0][2] = H->data.db[2];
  H_[1][0] = H->data.db[3];
  H_[1][1] = H->data.db[4];
  H_[1][2] = H->data.db[5];
  H_[2][0] = H->data.db[6];
  H_[2][1] = H->data.db[7];
  H_[2][2] = H->data.db[8];
  //cvInvert( H, H_inv, CV_SVD );
  //inverse((const double*)H->data.db, H_inv->data.db);
  inverse(H_, H_inv_);
  //cvInitMatHeader( &X, 3, 1, CV_64FC1, x, CV_AUTOSTEP );
  //X = cvCreateMat(3, 1, CV_64FC1);
  //cvGEMM( H_inv, dD, -1, NULL, 0, &X, 0 );
  //matrixMultiply((const double*[3])H_inv->data.db, dD->data.db, X->data.db);
  matrixMultiply(H_inv_, dD_, X_);

  cvReleaseMat2( &dD );
  cvReleaseMat2( &H );
  //cvReleaseMat( &H_inv );

  *xi = -1.0f*X_[2][0];
  *xr = -1.0f*X_[1][0];
  *xc = -1.0f*X_[0][0];
  
  //#else
/*
  CvMat* dD, * H, * H_inv, X;
  double x[3] = { 0 };
  dD = deriv3D( r, c, t, m, b );
  H = hessian3D( r, c, t, m, b );
  H_inv = cvCreateMat( 3, 3, CV_64FC1 );
  cvInvert( H, H_inv, CV_SVD );
  cvInitMatHeader( &X, 3, 1, CV_64FC1, x, CV_AUTOSTEP );
  //X = cvCreateMat(3, 1, CV_64FC1);
  cvGEMM( H_inv, dD, -1, NULL, 0, &X, 0 );
  //matrixMultiply((const double*[3])H_inv->data.db, dD->data.db, X->data.db);
  
  cvReleaseMat( &dD );
  cvReleaseMat( &H );
  cvReleaseMat( &H_inv );

  *xi = x[2];
  *xr = x[1];
  *xc = x[0];*/
  //#endif
}

//-------------------------------------------------------

//! Computes the partial derivatives in x, y, and scale of a pixel.
CvMat2* FastHessian::deriv3D(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b)
{
  CvMat2* dI;
  double dx, dy, ds;

  dx = (m->getResponse(r, c + 1, t) - m->getResponse(r, c - 1, t)) / 2.0;
  dy = (m->getResponse(r + 1, c, t) - m->getResponse(r - 1, c, t)) / 2.0;
  ds = (t->getResponse(r, c) - b->getResponse(r, c, t)) / 2.0;
  
  dI = cvCreateMat2( 3, 1, CV_64FC1 );
  cvmSet2( dI, 0, 0, dx );
  cvmSet2( dI, 1, 0, dy );
  cvmSet2( dI, 2, 0, ds );

  return dI;
}

//-------------------------------------------------------

//! Computes the 3D Hessian matrix for a pixel.
CvMat2* FastHessian::hessian3D(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b)
{
  CvMat2* H;
  double v, dxx, dyy, dss, dxy, dxs, dys;

  v = m->getResponse(r, c, t);
  dxx = m->getResponse(r, c + 1, t) + m->getResponse(r, c - 1, t) - 2 * v;
  dyy = m->getResponse(r + 1, c, t) + m->getResponse(r - 1, c, t) - 2 * v;
  dss = t->getResponse(r, c) + b->getResponse(r, c, t) - 2 * v;
  dxy = ( m->getResponse(r + 1, c + 1, t) - m->getResponse(r + 1, c - 1, t) - 
          m->getResponse(r - 1, c + 1, t) + m->getResponse(r - 1, c - 1, t) ) / 4.0;
  dxs = ( t->getResponse(r, c + 1) - t->getResponse(r, c - 1) - 
          b->getResponse(r, c + 1, t) + b->getResponse(r, c - 1, t) ) / 4.0;
  dys = ( t->getResponse(r + 1, c) - t->getResponse(r - 1, c) - 
          b->getResponse(r + 1, c, t) + b->getResponse(r - 1, c, t) ) / 4.0;

  H = cvCreateMat2( 3, 3, CV_64FC1 );
  cvmSet2( H, 0, 0, dxx );
  cvmSet2( H, 0, 1, dxy );
  cvmSet2( H, 0, 2, dxs );
  cvmSet2( H, 1, 0, dxy );
  cvmSet2( H, 1, 1, dyy );
  cvmSet2( H, 1, 2, dys );
  cvmSet2( H, 2, 0, dxs );
  cvmSet2( H, 2, 1, dys );
  cvmSet2( H, 2, 2, dss );

  return H;
}

//-------------------------------------------------------
