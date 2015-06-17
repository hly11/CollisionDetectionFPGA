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

#ifndef UTILS_H
#define UTILS_H

#ifdef VISUALISE
#include "opencv/cv.h"
#endif
#include "ipoint.h"

#include <vector>

typedef unsigned char uint8_t;

#ifndef VISUALISE
typedef struct _IplImage {
int                  nSize;
int                  ID;
int                  nChannels;
int                  alphaChannel;
int                  depth;
char                 colorModel[4];
char                 channelSeq[4];
int                  dataOrder;
int                  origin;
int                  align;
int                  width;
int                  height;
struct _IplROI*      roi;
struct _IplImage*    maskROI;
void*                imageId;
//struct _IplTileInfo* tileInfo;
int                  imageSize;
char*                imageData;
int                  widthStep;
int                  BorderMode[4];
int                  BorderConst[4];
char*                imageDataOrigin;
} IplImage;

typedef struct _IplROI {
int coi;
int xOffset;
int yOffset;
int width;
int height;
} IplROI;
#endif
//! Display error message and terminate program
void error(const char *msg);

//! Show the provided image and wait for keypress
void showImage(const IplImage *img);

//! Show the provided image in titled window and wait for keypress
void showImage(char *title,const IplImage *img);

// Convert image to single channel 32F
IplImage* getGray(const IplImage *img);

//! Draw a single feature on the image
void drawIpoint(IplImage *img, Ipoint &ipt, int tailSize = 0);

//! Draw all the Ipoints in the provided vector
void drawIpoints(IplImage *img, std::vector<Ipoint> &ipts, int tailSize = 0);

//! Draw descriptor windows around Ipoints in the provided vector
void drawWindows(IplImage *img, std::vector<Ipoint> &ipts);

// Draw the FPS figure on the image (requires at least 2 calls)
void drawFPS(IplImage *img);

//! Draw a Point at feature location
void drawPoint(IplImage *img, Ipoint &ipt);

//! Draw a Point at all features
void drawPoints(IplImage *img, std::vector<Ipoint> &ipts);

//! Save the SURF features to file
void saveSurf(char *filename, std::vector<Ipoint> &ipts);

//! Load the SURF features from file
void loadSurf(char *filename, std::vector<Ipoint> &ipts);

//! Round float to nearest integer
inline int fRound(float flt)
{
  return (int) floor(flt+0.5f);
}

inline IplImage* createImage(const IplImage *img)
{
	IplImage *a = new IplImage;
	
	a->imageData = new char[sizeof(float)*img->width*img->height];
	a->width = img->width;
	a->height = img->height;
	a->widthStep = img->widthStep;
	
	return a;
}

inline IplImage* createImage(int width, int height)
{
	IplImage *a = new IplImage;
	
	a->imageData = new char[sizeof(float)*width*height];
	a->width = width;
	a->height = height;
	a->widthStep = width*sizeof(float);
	
	return a;
}

inline void releaseImage(const IplImage *img)
{
	delete [] img->imageData;
	delete img;
}

#endif
