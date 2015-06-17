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

#ifndef SURFLIB_H
#define SURFLIB_H

//#include <cv.h>
//#include <highgui.h>

#include <ctime>
#include <iostream>

#include "integral.h"
#include "fasthessian.h"
#include "surf.h"
#include "ipoint.h"
#include "utils.h"


//! Library function builds vector of described interest points
inline void surfDetDes(IplImage *img,  /* image to find Ipoints in */
                       std::vector<Ipoint> &ipts, /* reference to vector of Ipoints */
                       bool upright = false, /* run in rotation invariant mode? */
                       int octaves = OCTAVES, /* number of octaves to calculate */
                       int intervals = INTERVALS, /* number of intervals per octave */
                       int init_sample = INIT_SAMPLE, /* initial sampling step */
                       float thres = THRES /* blob response threshold */)
{
  // Create integral-image representation of the image
  clock_t start = clock();
  IplImage *int_img = Integral(img);
  clock_t end = clock();
  std::cout<< "OpenSURF1 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
  // Create Fast Hessian Object
  start = clock();
  FastHessian fh(int_img, img, ipts, octaves, intervals, init_sample, thres);
 
  // Extract interest points and store in vector ipts
  fh.getIpoints();
  end = clock();
  std::cout<< "OpenSURF2 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
  // Create Surf Descriptor Object
  start = clock();
  Surf des(int_img, ipts);
std::cout<<"asd"<<ipts.size();
  // Extract the descriptors for the ipts
  des.getDescriptors(upright);
end = clock();
std::cout<< "OpenSURF3 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
  // Deallocate the integral image
  #ifdef CVLOADIMAGE
  cvReleaseImage(&int_img);
  #else
  releaseImage(int_img);
  #endif
}

//! Library function builds vector of described interest points
void surfDetDes2(IplImage* int_img, IplImage *img,  /* image to find Ipoints in */
                       std::vector<Ipoint> &ipts, /* reference to vector of Ipoints */
                       bool upright = false, /* run in rotation invariant mode? */
                       int octaves = OCTAVES, /* number of octaves to calculate */
                       int intervals = INTERVALS, /* number of intervals per octave */
                       int init_sample = INIT_SAMPLE, /* initial sampling step */
                       float thres = THRES /* blob response threshold */)
{
  // Create integral-image representation of the image
   // Create Fast Hessian Object
  clock_t start = clock();
  FastHessian fh(int_img, img, ipts, octaves, intervals, init_sample, thres);
 
  // Extract interest points and store in vector ipts
  fh.getIpoints();
  clock_t end = clock();
  std::cout<< "OpenSURF2 took: " << float(end - start) / CLOCKS_PER_SEC  << " seconds" << std::endl;
}


//! Library function builds vector of interest points
inline void surfDet(IplImage *img,  /* image to find Ipoints in */
                    std::vector<Ipoint> &ipts, /* reference to vector of Ipoints */
                    int octaves = OCTAVES, /* number of octaves to calculate */
                    int intervals = INTERVALS, /* number of intervals per octave */
                    int init_sample = INIT_SAMPLE, /* initial sampling step */
                    float thres = THRES /* blob response threshold */)
{
  // Create integral image representation of the image
  IplImage *int_img = Integral(img);

  // Create Fast Hessian Object
  FastHessian fh(int_img, ipts, octaves, intervals, init_sample, thres);

  // Extract interest points and store in vector ipts
  fh.getIpoints();

  // Deallocate the integral image
  //cvReleaseImage(&int_img);
}




//! Library function describes interest points in vector
inline void surfDes(IplImage *img,  /* image to find Ipoints in */
                    std::vector<Ipoint> &ipts, /* reference to vector of Ipoints */
                    bool upright = false) /* run in rotation invariant mode? */
{ 
  // Create integral image representation of the image
  IplImage *int_img = Integral(img);

  // Create Surf Descriptor Object
  Surf des(int_img, ipts);

  // Extract the descriptors for the ipts
  des.getDescriptors(upright);
  
  // Deallocate the integral image
  //cvReleaseImage(&int_img);
}


#endif
