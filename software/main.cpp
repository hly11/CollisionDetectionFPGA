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

#include "surflib.h"
#include "kmeans.h"
#include <thread>
#include <atomic>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "ximage_filter.h"
#include "xVDMA.h"
#ifdef VISUALISE
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#endif

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
//-------------------------------------------------------
// In order to you use OpenSURF, the following illustrates
// some of the simple tasks you can do.  It takes only 1
// function call to extract described SURF features!
// Define PROCEDURE as:
//  - 1 and supply image path to run on static image
//  - 2 to capture from a webcam
//  - 3 to match find an object in an image (work in progress)
//  - 4 to display moving features (work in progress)
//  - 5 to show matches between static images
#define PROCEDURE 5

//-------------------------------------------------------

//IplImage *int_image_buf[2];
//Ipvec ipts_buf[2];
IplImage *int_first;
IplImage *int_second;
IplImage *int_third;
IpVec *ipts_first;
IpVec *ipts_second;
IpVec *ipts_third;
IpVec *ipts_match_first;
IpVec *ipts_match_second;
IpVec *ipts_match_third;
IplImage *img1_gray_first;
IplImage *img1_gray_second;
IplImage *img1_gray_third;
IplImage *img2_gray_first;
IplImage *img2_gray_second;
IplImage *img2_gray_third;
std::atomic<int> int_done;
std::atomic<int> int2_done;

int mainImage(void)
{
  // Declare Ipoints and other stuff
  IpVec ipts;
  #ifdef USEOPENCV
  IplImage *img=cvLoadImage("imgs/img0005.jpg");
  //IplImage *img;

  // Detect and describe interest points in the image
  clock_t start = clock();
  //surfDetDes(img, ipts, false, 5, 4, 2, 0.0004f); 
  surfDetDes(img, ipts, true, 4, 2, 2, 0.01f);
  clock_t end = clock();

  std::cout<< "OpenSURF found: " << ipts.size() << " interest points" << std::endl;
  std::cout<< "OpenSURF took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;

  // Draw the detected points
  drawIpoints(img, ipts);
  
  // Display the result
  showImage(img);

  #endif
  return 0;
}

//-------------------------------------------------------
/*
int mainVideo(void)
{
  // Initialise capture device
  CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
  if(!capture) error("No Capture");

  // Initialise video writer
  //cv::VideoWriter vw("c:\\out.avi", CV_FOURCC('D','I','V','X'),10,cvSize(320,240),1);
  //vw << img;

  // Create a window 
  cvNamedWindow("OpenSURF", CV_WINDOW_AUTOSIZE );

  // Declare Ipoints and other stuff
  IpVec ipts;
  IplImage *img=NULL;

  // Main capture loop
  while( 1 ) 
  {
    // Grab frame from the capture source
    img = cvQueryFrame(capture);

    // Extract surf points
    surfDetDes(img, ipts, false, 4, 4, 2, 0.004f);    

    // Draw the detected points
    drawIpoints(img, ipts);

    // Draw the FPS figure
    drawFPS(img);

    // Display the result
    cvShowImage("OpenSURF", img);

    // If ESC key pressed exit loop
    if( (cvWaitKey(10) & 255) == 27 ) break;
  }

  cvReleaseCapture( &capture );
  cvDestroyWindow( "OpenSURF" );
  return 0;
}


//-------------------------------------------------------


int mainMatch(void)
{
  // Initialise capture device
  CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
  if(!capture) error("No Capture");

  // Declare Ipoints and other stuff
  IpPairVec matches;
  IpVec ipts, ref_ipts;
  
  // This is the reference object we wish to find in video frame
  // Replace the line below with IplImage *img = cvLoadImage("imgs/object.jpg"); 
  // where object.jpg is the planar object to be located in the video
  IplImage *img = cvLoadImage("imgs/object.jpg"); 
  if (img == NULL) error("Need to load reference image in order to run matching procedure");
  CvPoint src_corners[4] = {{0,0}, {img->width,0}, {img->width, img->height}, {0, img->height}};
  CvPoint dst_corners[4];

  // Extract reference object Ipoints
  surfDetDes(img, ref_ipts, false, 3, 4, 3, 0.004f);
  drawIpoints(img, ref_ipts);
  showImage(img);

  // Create a window 
  cvNamedWindow("OpenSURF", CV_WINDOW_AUTOSIZE );

  // Main capture loop
  while( true ) 
  {
    // Grab frame from the capture source
    img = cvQueryFrame(capture);
     
    // Detect and describe interest points in the frame
    surfDetDes(img, ipts, false, 3, 4, 3, 0.004f);

    // Fill match vector
    getMatches(ipts,ref_ipts,matches);
    
    // This call finds where the object corners should be in the frame
    if (translateCorners(matches, src_corners, dst_corners))
    {
      // Draw box around object
      for(int i = 0; i < 4; i++ )
      {
        CvPoint r1 = dst_corners[i%4];
        CvPoint r2 = dst_corners[(i+1)%4];
        cvLine( img, cvPoint(r1.x, r1.y),
          cvPoint(r2.x, r2.y), cvScalar(255,255,255), 3 );
      }

      for (unsigned int i = 0; i < matches.size(); ++i)
        drawIpoint(img, matches[i].first);
    }

    // Draw the FPS figure
    drawFPS(img);

    // Display the result
    cvShowImage("OpenSURF", img);

    // If ESC key pressed exit loop
    if( (cvWaitKey(10) & 255) == 27 ) break;
  }

  // Release the capture device
  cvReleaseCapture( &capture );
  cvDestroyWindow( "OpenSURF" );
  return 0;
}


//-------------------------------------------------------


int mainMotionPoints(void)
{
  // Initialise capture device
  CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
  if(!capture) error("No Capture");

  // Create a window 
  cvNamedWindow("OpenSURF", CV_WINDOW_AUTOSIZE );

  // Declare Ipoints and other stuff
  IpVec ipts, old_ipts, motion;
  IpPairVec matches;
  IplImage *img;

  // Main capture loop
  while( 1 ) 
  {
    // Grab frame from the capture source
    img = cvQueryFrame(capture);

    // Detect and describe interest points in the image
    old_ipts = ipts;
    surfDetDes(img, ipts, true, 3, 4, 2, 0.0004f);

    // Fill match vector
    getMatches(ipts,old_ipts,matches);
    for (unsigned int i = 0; i < matches.size(); ++i) 
    {
      const float & dx = matches[i].first.dx;
      const float & dy = matches[i].first.dy;
      float speed = sqrt(dx*dx+dy*dy);
      if (speed > 5 && speed < 30) 
        drawIpoint(img, matches[i].first, 3);
    }
        
    // Display the result
    cvShowImage("OpenSURF", img);

    // If ESC key pressed exit loop
    if( (cvWaitKey(10) & 255) == 27 ) break;
  }

  // Release the capture device
  cvReleaseCapture( &capture );
  cvDestroyWindow( "OpenSURF" );
  return 0;
}
*/

//-------------------------------------------------------

void filterMatches(IpPairVec& matches, IpPairVec& filtered_matches)
{
	for(int i=0;i<matches.size();i++)
	{
		if(matches[i].second.scale > matches[i].first.scale)
			filtered_matches.push_back(matches[i]);
	}
}

inline int trunc_coords(int x, int size)
{
	size = -1 + size;
	if(x >=0 && x <=size)
		return x;
	else if(x < 0)
		return 0;
	else
		return size;
}

inline void fast_getPixel(float *image, int x, int y, int sx, float *R)
{
    // Get the colour at pixel x,y in the image and return it using the provided RGB pointers
    // Requires the image size along the x direction!
    *R=image[x+y*sx];
}

inline void fast_setPixel(float *image, int x, int y, int sx, float R)
{
    // Set the colour of the pixel at x,y in the image to the specified R,G,B
    // Requires the image size along the x direction!
    image[x+y*sx]=R;
}

void build_dx_table(double* table,double dx)
{
	dx=dx/255.0f;
    unsigned len = 0xff;
    table[0] = 0;
    for (unsigned i=1;i<len;i++)
    {
        table[i] = table[i-1]+dx;
    }
}

float *fast_rescale(float *src, int src_x, int src_y, int dest_x, int dest_y, float* scaledquery)
{
    double step_x,step_y;          // Step increase as per instructions above
    float R1,R2,R3,R4;     // Colours at the four neighbours
    double RT1;          // Interpolated colours at T1 and T2
    double RT2;
    float R;           // Final colour at a destination pixel
    float *dst;            // Destination image - must be allocated here!
    int x,y;               // Coordinates on destination image
    double fx,fy;              // Corresponding coordinates on source image
    double dx,dy;              // Fractional component of source image    coordinates
    double dxtable[0xff];

    //dst=(unsigned char *)calloc(dest_x*dest_y*3,sizeof(unsigned char));   // Allocate and clear   destination image
	//dst=new float[dest_x*dest_y];
	dst=scaledquery;
    if (!dst) return(NULL);                           // Unable to allocate image

    step_x=(double)(src_x-1)/(double)(dest_x-1);
    step_y=(double)(src_y-1)/(double)(dest_y-1);

    for (x=0,fx=0;x<dest_x;x++,fx+=step_x)         // Loop over destination image
	{
        dx=fx-(int)fx;
        //build_dx_table(dxtable,dx);
        for (y=0,fy=0;y<dest_y;y++,fy+=step_y)
        {
            dy=fy-(int)fy;
		
            fast_getPixel(src,floor(fx),floor(fy),src_x,&R1);    // get N1 colours
            fast_getPixel(src,std::min<int>(ceil(fx),src_x-1),floor(fy),src_x,&R2); // get N2 colours
            fast_getPixel(src,floor(fx),std::min<int>(ceil(fy),src_y-1),src_x,&R3); // get N3 colours
            fast_getPixel(src,std::min<int>(ceil(fx),src_x-1),std::min<int>(ceil(fy),src_y-1),src_x,&R4);  // get N4 colours
            // Interpolate to get T1 and T2 colours

			float R1_R2_ = R2-R1;
			float R3_R4_ = R4-R3;
			//std::cerr<<R1_R2_<<std::endl;
			//std::cerr<<R3_R4_<<std::endl;
			RT1=R1+(R1_R2_)*dx;
			RT2=R3+(R3_R4_)*dx;
			
            // Obtain final colour by interpolating between T1 and T2
            R=dy*(RT2-RT1)+RT1;
            // Store the final colour
            fast_setPixel(dst,x,y,dest_x,R	);
        }
	}
    return(dst);
}

float* querypatch = new float[640*480];
float* trainpatch = new float[640*480];
float* scaledquery = new float[640*480];
float* scaledtrain = new float[640*480];
float scale[21];
float SEARCH_RES = 20.0f;
float MINSIZE = 1.2f;
float KEYPOINT_SCALE = SEARCH_RES;
float res[21];

int patch(float *img, float *patch, int x, int y, int r, int width, int height, int &width2, int &height2)
{
	int x0 = trunc_coords(x-r, width);
	int y0 = trunc_coords(y-r, height);
	int x1 = trunc_coords(x+r, width);
	int y1 = trunc_coords(y+r, height);
	int size = (x1-x0+1)*(y1-y0+1);
	width2 = x1-x0+1;
	height2 = y1-y0+1;
	
	if(x1-x0 > 0 && y1-y0 > 0)
	{
		float acc=0;
		float acc2=0;
		int step = x1-x0+1;
		for(int i2=0;i2<=(y1-y0);i2++)
		{
			for(int a=0;a<=(x1-x0);a++)
			{
				float *imgf = img;
				patch[i2*step+a]=imgf[(y0+i2)*width+(x0+a)];
				acc += patch[i2*step+a];
				acc2 += patch[i2*step+a]*patch[i2*step+a];
			}
		}
		
		float mean = acc/size;
		float mean_sq = acc2/size;
		float std = mean_sq - mean*mean;
		
		for(int i2=0;i2<size;i2++)
		{
			patch[i2] = (patch[i2]-mean)/std;
		}
		
		return 1;
	}
	else
		return 0;
}

int oldx, oldy;

int patch2(float *img, float *patch, int x, int y, int r, int width, int height, int &width2, int &height2)
{
	int x0 = trunc_coords(x-r, width);
	int y0 = trunc_coords(y-r, height);
	int x1 = trunc_coords(x+r, width);
	int y1 = trunc_coords(y+r, height);
	int size = (x1-x0+1)*(y1-y0+1);
	width2 = x1-x0+1;
	height2 = y1-y0+1;
	
	if(width2 == oldx && height2 == oldy)
		return 0;
	
	oldx = width2;
	oldy = height2;
	
	if(x1-x0 > 0 && y1-y0 > 0)
	{
		int step = x1-x0+1;
		for(int i2=0;i2<=(y1-y0);i2++)
		{
			for(int a=0;a<=(x1-x0);a++)
			{
				float *imgf = img;
				patch[i2*step+a]=imgf[(y0+i2)*width+(x0+a)];
			}
		}		
		return 1;
	}
	else
		return 0;
}

#define HLS_ADDR2 0x43000000

XImage_filter HLSDevice2;

volatile float * imgpatch;
volatile float * trainframe;
unsigned int imgpatch_xdma;
unsigned int trainframe_xdma;
int HLSDevice2_init;
int xVDMA2_init;
float oldacc;

#define VDMAPixelWidth 4
xVDMA_info vdma_;
xVDMA_info vdma_2;

inline timespec diff(timespec start, timespec end)
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

void estimateKeypointExpansion(IpPairVec &filtered_matches, IpPairVec &expand_matches, IplImage *img1, IplImage *img2)
{
	struct timespec time1,time2;
	
	int fd;
	if(HLSDevice2_init == 0)
	{
	  #define XDMA_IOCTL_BASE	'W'
#define XDMA_GET_DEV_INFO	_IO(XDMA_IOCTL_BASE, 1)
#define XDMA_GET_NUM_DEVICES	_IO(XDMA_IOCTL_BASE, 0)
		HLSDevice2_init = 1;
		HLSDevice2 = setup_ximage_filter(HLS_ADDR2);
	
		fd = open("/dev/xdma", O_RDWR);	
		if (fd < 1) {
				printf("Unable to open DMA proxy device file");
				return;
			}
		int bufi=7;
		ioctl(fd, XDMA_GET_DEV_INFO, &bufi);
		imgpatch = (float*)mmap(NULL, 1250000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x400000*(7));
		ioctl(fd, XDMA_GET_NUM_DEVICES, &imgpatch_xdma);
		
		bufi=8;
		ioctl(fd, XDMA_GET_DEV_INFO, &bufi);
		trainframe = (float*)mmap(NULL, 1250000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x400000*(8));
		ioctl(fd, XDMA_GET_NUM_DEVICES, &trainframe_xdma);
		/*
		for(int i=0;i<6;i++)
		{
		bufi=i+1;
		ioctl(fd, XDMA_GET_DEV_INFO, &bufi);
		outframe[i] = (float*)mmap(NULL, 3500000, 
											PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x400000*(i+1));
		ioctl(fd, XDMA_GET_NUM_DEVICES, &outframe_xdma[i]);
		}*/
	}
	
	if(xVDMA2_init == 0)
	{	
        xVDMA_Init(&vdma_, 0x43C00000, 5, 5, VDMAPixelWidth);
		xVDMA_Init(&vdma_2, 0x43C10000, 10, 10, VDMAPixelWidth);
		xVDMA2_init = 1;
	}
	
	for(int i=0; i<filtered_matches.size(); i++)
	{
		int x_qkp = filtered_matches[i].first.x; int y_qkp = filtered_matches[i].first.y;
        int r = filtered_matches[i].first.scale * KEYPOINT_SCALE / 2.0f;
		int querypatch_width;
		int querypatch_height;		
		
		if(!patch((float*)img1->imageData, (float*)imgpatch, x_qkp, y_qkp, r, img1->width, img1->height, querypatch_width, querypatch_height))
			continue;
		
		int x_tkp = filtered_matches[i].second.x; int y_tkp = filtered_matches[i].second.y;
        r = filtered_matches[i].first.scale * KEYPOINT_SCALE * scale[20] / 2.0f;
		int trainpatch_width;
		int trainpatch_height;
		
		if(!patch((float*)img2->imageData, trainpatch, x_tkp, y_tkp, r, img2->width, img2->height, trainpatch_width, trainpatch_height))
			continue;
		int x0 = trunc_coords(x_tkp-r, img2->width);
		int y0 = trunc_coords(y_tkp-r, img2->height);
		
		x_tkp = x_tkp-x0;
		y_tkp = y_tkp-y0;
		oldx = 0;
		oldy = 0;
		oldacc = FLT_MAX;
		for(int i3=0;i3<21;i3++)
		{
			r = filtered_matches[i].first.scale * KEYPOINT_SCALE * scale[i3] / 2.0f;
			int scaledquery_width;
			int scaledquery_height;
			
			if(patch2(trainpatch, (float*)trainframe, x_tkp, y_tkp, r, trainpatch_width, trainpatch_height, scaledquery_width, scaledquery_height))
			{
				while(!XImage_filter_IsReady(&HLSDevice2)){}
				/*char b_[20] = "new/img0000.jpg";
	int i2=0;
		
		sprintf(b_, "new/img%04i.jpg",i2+1);
	cv::Mat inFrame,outFrame;
	inFrame = cv::imread(b_);
	//cv::integral(inFrame,outFrame);
	//inFrame = outFrame;
	cvtColor(inFrame, inFrame, CV_RGB2GRAY);
	inFrame.convertTo(inFrame, CV_32FC1);
	inFrame=inFrame*1.0f/255.0f;
				*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x18) = 5;
				*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x20) = 5;
				*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x28) = 15;
				*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x30) = 10;
				
				cv::Rect myROI(0, 0, 5, 5);
	cv::Rect myROI2(0, 0, 10, 15);

	cv::Mat region = inFrame(myROI);
	cv::Mat region2 = inFrame(myROI2);

	cv::Mat region_out(region2.size(), region2.type());

	cv::Mat region_;
	region.copyTo(region_);

	cv::Mat region2_temp;
	region2.copyTo(region2_temp);

	cv::resize(region, region_out, region_out.size(), 0, 0);
float res2 =0.0f;
	for(int i=0;i<15;i++)
	{
		for(int asd=0;asd<10;asd++)
		{
			float temp = region2.at<float>(i,asd) - region_out.at<float>(i,asd);
			res2 += temp*temp;
		}
	}
	res2=sqrtf(res2);
	std::cout<<res2<<std::endl;
	
	memcpy((void*)imgpatch, region_.data, 5*5*4);
	memcpy((void*)trainframe, region2_temp.data, 10*15*4);*/
	//std::cout<<"1"<<std::endl;
	*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x18) = querypatch_height;
				*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x20) = querypatch_width;
				*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x28) = scaledquery_height;
				*(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x30) = scaledquery_width;
				unsigned int temp = *(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress+0x18);
	temp += *(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress+0x20);
	temp += *(volatile unsigned int*)(HLSDevice2.Control_bus_BaseAddress + 0x28);
	temp += *(volatile unsigned int*)((HLSDevice2.Control_bus_BaseAddress + 0x30));
	//std::cout<<temp;
/*				std::cerr<<"q"<<querypatch_height<<" "<<querypatch_width<<" "<<scaledquery_height<<" "<<scaledquery_width<<std::endl;*/
				vdma_.height = querypatch_height;
				vdma_.width = querypatch_width;
				vdma_2.height = scaledquery_height;
				vdma_2.width = scaledquery_width;
				 //xVDMA_Init(&vdma_, 0x43C00000, querypatch_width, querypatch_height, VDMAPixelWidth);
		//xVDMA_Init(&vdma_2, 0x43C10000, scaledquery_width, scaledquery_height, VDMAPixelWidth);
				xVDMA_Set(&vdma_, 0x00/4, 4);
				xVDMA_Set(&vdma_2, 0x00/4, 4);
				while((xVDMA_Get(&vdma_, 0x00/4)&0x4)==4||(xVDMA_Get(&vdma_2, 0x00/4)&0x4)==4){};
				//XImage_filter_Set_cols(&HLSDevice,9);
				clock_gettime(CLOCK_REALTIME, &time1);
				while(!XImage_filter_IsReady(&HLSDevice2)){}
				XImage_filter_Start(&HLSDevice2);
				//xVDMA_kick2(&vdma, INPUT_FRAME_ADDR);
				//xVDMA_kick2(&vdma2, OUTPUT_FRAME_ADDR);
				xVDMA_kick(&vdma_, imgpatch_xdma, 0x38400000);
				xVDMA_kick(&vdma_2, trainframe_xdma, 0x38800000);
				while(!XImage_filter_IsDone(&HLSDevice2)){}
				clock_gettime(CLOCK_REALTIME, &time2);
				//std::cout<<diff(time1,time2).tv_sec<<":"<<diff(time1,time2).tv_nsec<<std::endl;
				//fast_rescale((float*)imgpatch, querypatch_width, querypatch_height, scaledquery_width, scaledquery_height, scaledquery);//scaledquery = cv2.resize(querypatch,scaledtrain.shape[::-1]
                                     //, fx=scale, fy=scale
                                     //, interpolation=cv2.INTER_LINEAR)
				
				//float *scaledquery = new float[size];
				//cv::Mat imgquery(querypatch_height, querypatch_width, CV_32FC1, (float*)imgpatch);
				//cv::Mat imgscale(scaledquery_height, scaledquery_width, CV_32FC1, scaledquery);
				//cv::resize(imgquery, imgscale, imgscale.size(), 0, 0);
				/*				
									 float minquery=FLT_MAX,maxquery=0;
		for(int i2=0;i2<size;i2++)
			{
				if(scaledquery[i2]<minquery)
					minquery=scaledquery[i2];
					
				if(scaledquery[i2]>minquery)
					maxquery=scaledquery[i2];
			}
			float *scaledquery2 = new float[size];
			float *scaledtrain2 = new float[size];
		for(int i2=0;i2<size;i2++)
			{
				scaledquery2[i2] = (scaledquery[i2]-minquery)/(maxquery-minquery);
			}
			minquery=FLT_MAX,maxquery=0;
		for(int i2=0;i2<size;i2++)
			{
				if(scaledtrain[i2]<minquery)
					minquery=scaledtrain[i2];
					
				if(scaledtrain[i2]>minquery)
					maxquery=scaledtrain[i2];
			}
			for(int i2=0;i2<size;i2++)
			{
				scaledtrain2[i2] = (scaledtrain[i2]-minquery)/(maxquery-minquery);
			}
		cv::Mat img(scaledquery_height, scaledquery_width, CV_32FC1, scaledquery);
		cv::namedWindow( "Display window", CV_WINDOW_NORMAL );
		cv::imshow("Display window",img);
		cv::Mat img2(scaledquery_height, scaledquery_width, CV_32FC1, scaledtrain);
		cv::namedWindow( "Display window2", CV_WINDOW_NORMAL );
		cv::imshow("Display window2",img2);
		cvWaitKey(0);			*/
		
				/*float acc=0;
				for(int i4=0;i4<scaledquery_width*scaledquery_height;i4++)
				{
					acc += (scaledquery[i4]-trainframe[i4])*(scaledquery[i4]-trainframe[i4]);
				}
				acc = sqrt(acc);*/
				float acc2=FLT_MAX;	
				memcpy(&acc2,(void*)(HLSDevice2.Control_bus_BaseAddress+0x10),4);
				//std::cerr<<"acc"<<acc<<std::endl;
				//std::cerr<<"res"<<acc2<<std::endl;
				//return;
				res[i3]=acc2;
				oldacc=acc2;
			}
			else
				res[i3]=oldacc;//res[i3]=FLT_MAX;
		}
		
		for(int i3=0;i3<21;i3++)
		{
			res[i3]=res[i3]/scale[i3]/scale[i3];
		}
		
		int res_argmin=-1;
		float tempmin=FLT_MAX;
		for(int i3=0;i3<21;i3++)
		{
			if(res[i3] < tempmin)
			{
				res_argmin=i3;
				tempmin=res[i3];
			}
		}
		
		float scalemin=scale[res_argmin];
		#ifdef DEBUG
		std::cerr<<"matched scale "<<scalemin<<std::endl;
			std::cerr<<"nearest neighbour ratio "<<res[res_argmin]/res[0]<<std::endl;
			std::cerr<<"residuals [";
			for(int i2=0;i2<21;i2++)
			{
				std::cerr<<res[i2]<<" ";
			}
			std::cerr<<std::endl;
		#endif
		if(scalemin>=MINSIZE && res[res_argmin] < 0.6*res[0])
		{
			expand_matches.push_back(filtered_matches[i]);
			filtered_matches[i].second.scale = filtered_matches[i].first.scale*scalemin;
		}
	}
}

void FastHessian2()
{
	int_done.store(1);
	while(true)
	{
		if(int_second && ipts_second)
		{
			surfDetDes2(int_second,int_second,*ipts_second,true,2,2,2,0.005f);
			//int_done=1;
			int_done.store(1);
		}
		while(int_done.load()){}
	}
}

void SURF_estimateKeypointExpansion()
{
	int2_done.store(1);
	while(true)
	{
		if(int_third && ipts_third)
		{
			Surf des(int_third, *ipts_third);
			std::cout<<"asd"<<(*ipts_third).size();
			  // Extract the descriptors for the ipts
			  des.getDescriptors(true);
 	

			IpPairVec matches, filtered_matches, expand_matches;
			clock_t start2 = clock();
			getMatches(*ipts_match_third,*ipts_third,matches);
			//start = clock();
		filterMatches(matches, filtered_matches);
			estimateKeypointExpansion(filtered_matches, expand_matches, img1_gray_third, img2_gray_third);
			matches=expand_matches;
			std::cout<<matches.size()<<std::endl;
			if(matches.size()>3)
				std::cout<<"COLLISION"<<std::endl;
/*
#ifdef VISUALISE
	IplImage *img1 = (IplImage*) cvClone(img1_gray_third);
	IplImage *img2 = (IplImage*) cvClone(img2_gray_third);
	for (unsigned int i = 0; i < matches.size(); ++i)
	{
		drawIpoint(img1,matches[i].first,0);
		drawIpoint(img2,matches[i].second,0);


		const int & w = img1->width;
		cvLine(img1,cvPoint(matches[i].first.x,matches[i].first.y),cvPoint(matches[i].second.x+w,matches[i].second.y), cvScalar(255,255,255),1);
		cvLine(img2,cvPoint(matches[i].first.x-w,matches[i].first.y),cvPoint(matches[i].second.x,matches[i].second.y), cvScalar(255,255,255),1);
	}
	#endif
	#ifdef VISUALISE
	cvNamedWindow("1", CV_WINDOW_AUTOSIZE );
	cvNamedWindow("2", CV_WINDOW_AUTOSIZE );
	cvShowImage("1", img1);

	cvShowImage("2", img2);
	cvWaitKey(expand_matches.size() > 3? 0:10);
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	#endif*/
		  #ifdef CVLOADIMAGE
			  cvReleaseImage(&int_third);
			  cvReleaseImage(&img1_gray_third);
			  delete ipts_match_third;
			  #else
			  releaseImage(int_third);
			  #endif
			//int2_done=1;
			int2_done.store(1);
		}
		while(int2_done.load()){}
	}
}

inline IplImage* loadImage(char *a, IplImage **img=0);			
int mainStaticMatch(char *a, char *b);	
int mainStaticMatch2(int argc, char *argv[])
{
	//std::string a, b;
	
	char a_[20] = "new/img0000.jpg";
	char b_[20] = "new/img0000.jpg";
	char c_[20] = "new/images.h";
	int nSkip=5;

	timespec time1, time2;
	
	for(int i=0; i<21; i++)
	{
		scale[i] = 1.0f+(float)i/40.0f;
	}
	std::vector<std::pair<IplImage*,IpVec*>> imgbuffer;
	#ifdef VISUALISE
	std::vector<IplImage*> imgbuffer1;
	#endif
	int i3=1;
	float start1=0;
	while(true)
	{
	imgbuffer.clear();
	#ifdef VISUALISE
	imgbuffer1.clear();
	#endif
	//std::ofstream ofs (c_, std::ofstream::out|std::ofstream::app);
	//ofs << "unsigned char imgs[][640*480]={"d;
	for(int i=0;i<=nSkip;i++)
	{
		sprintf(b_, "new/img%04i.jpg",i+1);
		#ifdef VISUALISE
		IplImage *img1;
		IplImage *img1_gray = loadImage(b_,&img1);
		imgbuffer1.push_back(img1);
		#else
		IplImage *img1_gray = loadImage(b_);
		#endif
		
		imgbuffer.push_back(std::make_pair(img1_gray, new IpVec));
		surfDetDes(imgbuffer[i].first,*imgbuffer[i].second,true,2,2,2,0.005f);
		/*
		IplImage *img1_ = cvLoadImage(b_,CV_LOAD_IMAGE_GRAYSCALE);	
		ofs << "{";
		for(int i2=0;i2<img1_->width*img1_->height-1;i2++)
		{
			unsigned char a = img1_->imageData[i2];
			ofs<<std::setbase(16)<<std::setfill('0')<<std::setw(2)<<" 0x"<<(unsigned)a<<",";
		}
		unsigned char a = img1_->imageData[img1_->width*img1_->height-1];
		ofs<<std::setbase(16)<<std::setfill('0')<<std::setw(2)<<" 0x"<<(unsigned)a;
		ofs<<"},";*/
	}

	//std::thread first(load_and_integral);
	std::thread first(FastHessian2);
	std::thread second(SURF_estimateKeypointExpansion);

	first.detach();
	second.detach();
	
	for(int i=nSkip+1;i<123;i++,i3++)
	{
	//clock_t start = clock();
	clock_gettime(CLOCK_REALTIME, &time1);
	sprintf(b_, "new/img%04i.jpg",i+1);
	IplImage *img2;
	#ifdef VISUALISE
	IplImage *img1=imgbuffer1[i-nSkip-1];
	IplImage *img2_gray = loadImage(b_,&img2);
	//IplImage *img1_ = cvLoadImage(b_,CV_LOAD_IMAGE_GRAYSCALE);	
	/*ofs << "{";
	for(int i2=0;i2<img1_->width*img1_->height-1;i2++)
	{
		unsigned char a = img1_->imageData[i2];
		ofs<<std::setbase(16)<<std::setfill('0')<<std::setw(2)<<" 0x"<<(unsigned)a<<",";
	}
	unsigned char a = img1_->imageData[img1_->width*img1_->height-1];
	ofs<<std::setbase(16)<<std::setfill('0')<<std::setw(2)<<" 0x"<<(unsigned)a;
	if(i!=122)
		ofs<<"},";
	else
		ofs<<"}";
	//ofs.close();*/
	#else
	IplImage *img2_gray = loadImage(b_);
	#endif
	IplImage *img1_gray = imgbuffer[i-nSkip-1].first;
	#ifdef VISUALISE
	imgbuffer1.push_back(img2);
	img2=(IplImage*)cvClone(img2);
	#endif
	clock_gettime(CLOCK_REALTIME, &time1);
	//start=clock();
	imgbuffer.push_back(std::make_pair(img2_gray, new IpVec));
	clock_gettime(CLOCK_REALTIME, &time1);
//	start=clock();//surfDetDes(img2_gray,*imgbuffer[i].second,true,2,2,2,0.005f);
	//IplImage *int_img = Integral(img2_gray);
	int_first = Integral(img2_gray);
	ipts_first = imgbuffer[i].second;
	ipts_match_first = imgbuffer[i-nSkip-1].second;
	img1_gray_first = img1_gray;
	img2_gray_first = img2_gray;
	while((int_done.load()==0 || int2_done.load()==0) && (int_second && ipts_second) && (int_third && ipts_third)){}
	while(int_done.load()==0 && (int_second && ipts_second)){}
	int_third = int_second;
	ipts_third = ipts_second;
	ipts_match_third = ipts_match_second;
img1_gray_third = img1_gray_second;
	img2_gray_third = img2_gray_second;
	int_second = int_first;
	ipts_second = ipts_first;
	ipts_match_second = ipts_match_first;
img1_gray_second = img1_gray_first;
	img2_gray_second = img2_gray_first;
	int_done.store(0);
	if(int_third && ipts_third) int2_done.store(0);
clock_t end = clock();
clock_gettime(CLOCK_REALTIME, &time2);
//start1 += end - start;
start1 += (float)diff(time1, time2).tv_nsec/1e9;
//std::cout<< "OpenSURF took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
//	std::cout<< "FPS: " << (i3) /(float(start1) / CLOCKS_PER_SEC)  << "" << std::endl;

std::cout<< "OpenSURF took: " << diff(time1, time2).tv_nsec  << " seconds" << std::endl;
	std::cout<< "FPS: " << (i3) /(float(start1))  << "" << std::endl;
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	continue;
	/*IpPairVec matches, filtered_matches, expand_matches;
	clock_t start2 = clock();
	getMatches(*imgbuffer[i-nSkip-1].second,*imgbuffer[i].second,matches);
	//start = clock();
filterMatches(matches, filtered_matches);
	estimateKeypointExpansion(filtered_matches, expand_matches, img1_gray, img2_gray);
	matches=expand_matches;
	
	clock_t end = clock();
	start1 += end - start;
	std::cerr<< "Matches: " << matches.size();
	std::cerr<<std::endl<< "Filtered Matches: " << filtered_matches.size();
	std::cerr<<std::endl<< "Expanding Matches: " << expand_matches.size();
	std::cout<< std::endl << "OpenSURF found: " << (*imgbuffer[i-nSkip-1].second).size() << " " << (*imgbuffer[i].second).size() << " interest points" << std::endl;
	std::cout<< "OpenSURF6 took: " << float(end - start2) / CLOCKS_PER_SEC  << " seconds" << std::endl;
	std::cout<< "OpenSURF took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
	std::cout<< "FPS: " << (i3) /(float(start1) / CLOCKS_PER_SEC)  << "" << std::endl;
  //#endif
	#ifdef VISUALISE
	for (unsigned int i = 0; i < matches.size(); ++i)
	{
		drawIpoint(img1,matches[i].first,0);
		drawIpoint(img2,matches[i].second,0);

		const int & w = img1->width;
		cvLine(img1,cvPoint(matches[i].first.x,matches[i].first.y),cvPoint(matches[i].second.x+w,matches[i].second.y), cvScalar(255,255,255),1);
		cvLine(img2,cvPoint(matches[i].first.x-w,matches[i].first.y),cvPoint(matches[i].second.x,matches[i].second.y), cvScalar(255,255,255),1);
	}
	#endif
	#ifdef VISUALISE
	cvNamedWindow("1", CV_WINDOW_AUTOSIZE );
	cvNamedWindow("2", CV_WINDOW_AUTOSIZE );
	cvShowImage("1", img1);
	cvShowImage("2", img2);
	cvWaitKey(expand_matches.size() > 3? 0:10);
	#endif
	#ifdef CVLOADIMAGE
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	//cvReleaseImage(&img1_gray);
	cvReleaseImage(&img1_gray);
	#else
	releaseImage(img1_gray);
	#endif
	delete imgbuffer[i-nSkip-1].second;*/
	}
	//ofs <<"};";
	//ofs.close();
while((int_done.load()==0 || int2_done.load()==0)){}
	int_third = int_second;
	ipts_third = ipts_second;
	ipts_match_third = ipts_match_second;
img1_gray_third = img1_gray_second;
	img2_gray_third = img2_gray_second;
	int_second = int_first;
	ipts_second = ipts_first;
	ipts_match_second = ipts_match_first;
img1_gray_second = img1_gray_first;
	img2_gray_second = img2_gray_first;
	int_done.store(0);
	int2_done.store(0);
while((int_done.load()==0 || int2_done.load()==0)){}
	int_third = int_second;
	ipts_third = ipts_second;
	ipts_match_third = ipts_match_second;
img1_gray_third = img1_gray_second;
	img2_gray_third = img2_gray_second;
	int_second = int_first;
	ipts_second = ipts_first;
	ipts_match_second = ipts_match_first;
img1_gray_second = img1_gray_first;
	img2_gray_second = img2_gray_first;
	//int_done.store(0);
	int2_done.store(0);
while(int2_done.load()==0){}
	for(int i=123-nSkip-1;i<123;i++)
	{
		#ifdef CVLOADIMAGE
		cvReleaseImage(&imgbuffer1[i]);
		cvReleaseImage(&imgbuffer[i].first);
		#else
		releaseImage(imgbuffer[i].first);
		#endif
		delete imgbuffer[i].second;
	}
	}
	return 0;
}

inline IplImage* loadImage(char *a, IplImage **img)
{
  IplImage *img1, *img1_gray;
  int width, height;
  #ifdef CVLOADIMAGE
  img1 = cvLoadImage(a);
  img1_gray = getGray(img1);
  
  if(img)
	*img=img1;
  else
	cvReleaseImage(&img1);
  
  return img1_gray;
  #else
  width = 640;
  height = 480;
  
  size_t cbRaw = width*height;
  uint8_t* raw = new uint8_t[cbRaw];
  
  float* img1f;
  
  std::ifstream ifs (a, std::ifstream::in|std::ifstream::binary);
  
  ifs.seekg (0, ifs.end);
  int length = ifs.tellg();
  ifs.seekg (0, ifs.beg);
  ifs.read((char*)raw, length);

  img1 = createImage(width, height);
  img1f=(float*)img1->imageData;
  for(int i=0;i<length;i++)
  {
		img1f[i] = (float)(unsigned int)raw[i]/255.0f;
  }
  
  delete [] raw;
  
  return img1;
  #endif
}
  
  //int mainStaticMatch(int argc, char *argv[])
int mainStaticMatch(char *a, char *b)
{
  IplImage *img1, *img1_gray, *img2, *img2_gray;
  int width, height;
  
  #ifdef CVLOADIMAGE
  img1 = cvLoadImage(a);
  img2 = cvLoadImage(b);
  img1_gray = getGray(img1);
  img2_gray = getGray(img2);;
  #else
  width = 512;
  height = 512;
  
  size_t cbRaw = width*height;
  uint8_t* raw = new uint8_t[cbRaw];
  uint8_t* raw2 = new uint8_t[cbRaw];
  
  float* img1f;
  float* img2f;
  
  std::ifstream ifs (a, std::ifstream::in|std::ifstream::binary);
  std::ifstream ifs2 (b, std::ifstream::in|std::ifstream::binary);
  
  ifs.seekg (0, ifs.end);
  int length = ifs.tellg();
  ifs.seekg (0, ifs.beg);
  ifs.read((char*)raw, length);
  ifs2.read((char*)raw2, length);

  img1 = createImage(width, height);
  img2 = createImage(width, height);
  img1f=(float*)img1->imageData;
  img2f=(float*)img2->imageData;
  for(int i=0;i<length;i++)
  {
		img1f[i] = (float)(unsigned int)raw[i]/255.0f;
		img2f[i] = (float)(unsigned int)raw2[i]/255.0f;
  }
  
  delete [] raw;
  delete [] raw2;
  #endif
	
  clock_t start = clock();
  IpVec ipts1, ipts2;
  surfDetDes(img1_gray,ipts1,true,2,2,2,0.005f); //upright, octaves, intervals, init, thres
  surfDetDes(img2_gray,ipts2,true,2,2,2,0.005f);
  
  #ifdef VISUALISE/*
  img1 = cvLoadImage("imgs/img1.jpg");
  img2 = cvLoadImage("imgs/img1.jpg");
  img1 = getGray(img1);
  img2 = getGray(img2);
  img1->imageData = (char*)img1f;
  img2->imageData = (char*)img2f;*/
  #ifndef CVLOADIMAGE
  cv::Mat img1_mat(height, width, CV_32FC1, img1->imageData);
  cv::Mat img2_mat(height, width, CV_32FC1, img2->imageData);
  
  IplImage img11 = img1_mat;
  IplImage img21 = img2_mat;
  img1 = &img11;
  img2 = &img21;
  #endif
  #endif
  IpPairVec matches, filtered_matches, expand_matches;
  //clock_t start = clock();
  getMatches(ipts1,ipts2,matches);
  
  filterMatches(matches, filtered_matches);
  estimateKeypointExpansion(filtered_matches, expand_matches, img1_gray, img2_gray);
  matches=expand_matches;
  
  clock_t end = clock();
  //#ifdef DEBUG
  std::cerr<< "Matches: " << matches.size();
  std::cerr<<std::endl<< "Filtered Matches: " << filtered_matches.size();
  std::cerr<<std::endl<< "Expanding Matches: " << expand_matches.size();
  std::cout<< std::endl << "OpenSURF found: " << ipts1.size() << " " << ipts2.size() << " interest points" << std::endl;
  std::cout<< "OpenSURF took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
  //#endif
#ifdef VISUALISE
  for (unsigned int i = 0; i < matches.size(); ++i)
  {
    drawIpoint(img1,matches[i].first,0);
    drawIpoint(img2,matches[i].second,0);
  
    const int & w = img1->width;
    cvLine(img1,cvPoint(matches[i].first.x,matches[i].first.y),cvPoint(matches[i].second.x+w,matches[i].second.y), cvScalar(255,255,255),1);
    cvLine(img2,cvPoint(matches[i].first.x-w,matches[i].first.y),cvPoint(matches[i].second.x,matches[i].second.y), cvScalar(255,255,255),1);
  }
#endif
  saveSurf("1.txt", ipts1);
  saveSurf("2.txt", ipts2);
#ifdef VISUALISE
  cvNamedWindow("1", CV_WINDOW_AUTOSIZE );
  cvNamedWindow("2", CV_WINDOW_AUTOSIZE );
  cvShowImage("1", img1);
  cvShowImage("2", img2);
  cvWaitKey(matches.size() > 3? 0:10);
#endif
#ifdef CVLOADIMAGE
  cvReleaseImage(&img1);
  cvReleaseImage(&img2);
  cvReleaseImage(&img1_gray);
  cvReleaseImage(&img2_gray);

#else
  releaseImage(img1);
  releaseImage(img2);
#endif
  return 0;
}
/*
//-------------------------------------------------------

int mainKmeans(void)
{
  IplImage *img = cvLoadImage("imgs/img1.jpg");
  IpVec ipts;
  Kmeans km;
  
  // Get Ipoints
  surfDetDes(img,ipts,true,3,4,2,0.0006f);

  for (int repeat = 0; repeat < 10; ++repeat)
  {

    IplImage *img = cvLoadImage("imgs/img1.jpg");
    km.Run(&ipts, 5, true);
    drawPoints(img, km.clusters);

    for (unsigned int i = 0; i < ipts.size(); ++i)
    {
      cvLine(img, cvPoint(ipts[i].x,ipts[i].y), cvPoint(km.clusters[ipts[i].clusterIndex].x ,km.clusters[ipts[i].clusterIndex].y),cvScalar(255,255,255));
    }

    showImage(img);
  }

  return 0;
}
*/
//-------------------------------------------------------

int main(int argc, char *argv[]) 
{
  if (PROCEDURE == 1) return mainImage();
//  if (PROCEDURE == 2) return mainVideo();
//  if (PROCEDURE == 3) return mainMatch();
//  if (PROCEDURE == 4) return mainMotionPoints();
  if (PROCEDURE == 5) return mainStaticMatch2(argc, argv);
  //if (PROCEDURE == 6) return mainKmeans();
}
