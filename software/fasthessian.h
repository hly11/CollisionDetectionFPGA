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

#ifndef FASTHESSIAN_H
#define FASTHESSIAN_H

//#include <cv.h>
#include "ipoint.h"
#include "utils.h"

#include <vector>
#include <cstring>

class ResponseLayer;
static const int OCTAVES = 5;
static const int INTERVALS = 4;
static const float THRES = 0.0004f;
static const int INIT_SAMPLE = 2;

typedef unsigned char uchar;
#ifndef USEOPENCV
typedef struct CvMat2
{
int type;
int step;
/* for internal use only */
int* refcount;
int hdr_refcount;
union
{
uchar* ptr;
short* s;
int* i;
float* fl;
double* db;
} data;
#ifdef __cplusplus
union
{
int rows;
int height;
};
union
{
int cols;
int width;
};
#else
int rows;
int cols;
#endif
#ifdef __cplusplus
CvMat2() {}
CvMat2(const CvMat2& m) { memcpy(this, &m, sizeof(CvMat2));}
//CvMat(const cv::Mat& m);
#endif
}

#define CV_64FC1 0

CvMat2;

inline CvMat2* cvCreateMat2(int row, int column, int type)
{
	CvMat2 *a = new CvMat2;
	
	a->type=type;
	a->rows=row;
	a->cols=column;
	a->data.db = new double[row*column];
	a->step=sizeof(double)*a->cols;
	
	return a;
}

inline void cvReleaseMat2(CvMat2 **a)
{
	delete [] (*a)->data.db;
	delete *a;
}
#else
typedef CvMat CvMat2;
inline CvMat2* cvCreateMat2(int row, int column, int type)
{
	return cvCreateMat(row, column, type);
}
inline void cvReleaseMat2(CvMat2 **a)
{
	return cvReleaseMat(a);
}
#endif

inline double determinantOfMinor( int          theRowHeightY,
                           int          theColumnWidthX,
                           const double theMatrix [/*Y=*/3] [/*X=*/3] )
{
  int x1 = theColumnWidthX == 0 ? 1 : 0;  /* always either 0 or 1 */
  int x2 = theColumnWidthX == 2 ? 1 : 2;  /* always either 1 or 2 */
  int y1 = theRowHeightY   == 0 ? 1 : 0;  /* always either 0 or 1 */
  int y2 = theRowHeightY   == 2 ? 1 : 2;  /* always either 1 or 2 */

  return ( theMatrix [y1] [x1]  *  theMatrix [y2] [x2] )
      -  ( theMatrix [y1] [x2]  *  theMatrix [y2] [x1] );
}

inline double determinant( const double theMatrix [/*Y=*/3] [/*X=*/3] )
{
  return ( theMatrix [0] [0]  *  determinantOfMinor( 0, 0, theMatrix ) )
      -  ( theMatrix [0] [1]  *  determinantOfMinor( 0, 1, theMatrix ) )
      +  ( theMatrix [0] [2]  *  determinantOfMinor( 0, 2, theMatrix ) );
}

//#define ABS std::abs

inline bool inverse( const double theMatrix[3][3], double theOutput[3][3] )
{
  //double theMatrix[3][3];
  //double theOutput[3][3];
  double det = determinant( theMatrix );

    /* Arbitrary for now.  This should be something nicer... */
 // if ( det > 0 ? det : -det < (double)1e-2 )
  //{
  //  memset( theOutput, 0, sizeof theOutput );
  //  return false;
 // }

  double oneOverDeterminant = 1.0 / det;

  for (   int y = 0;  y < 3;  y ++ )
    for ( int x = 0;  x < 3;  x ++   )
    {
        /* Rule is inverse = 1/det * minor of the TRANSPOSE matrix.  *
         * Note (y,x) becomes (x,y) INTENTIONALLY here!              */
      theOutput [y] [x]
        = determinantOfMinor( x, y, theMatrix ) * oneOverDeterminant;

        /* (y0,x1)  (y1,x0)  (y1,x2)  and (y2,x1)  all need to be negated. */
      if( 1 == ((x + y) % 2) )
        theOutput [y] [x] = - theOutput [y] [x];
    }

  return true;
}

inline void matrixMultiply(  const double theMatrixA [/*Y=*/3] [/*X=*/3],
                      const double theMatrixB [/*Y=*/3] [/*X=*/1],
                            double theOutput  [/*Y=*/3] [/*X=*/1]  )
{
  for (   int y = 0;  y < 3;  y ++ )
    for ( int x = 0;  x < 1;  x ++   )
    {
      theOutput [y] [x] = 0;
      for ( int i = 0;  i < 3;  i ++ )
        theOutput [y] [x] +=  theMatrixA [y] [i] * theMatrixB [i] [x];
    }
}
#ifndef USEOPENCV
inline void cvmSet2(CvMat2 *a, int row, int column, double x)
{
	//row=0;
	a->data.db[row*a->width+column]=x;
}
#else
inline void cvmSet2(CvMat2 *a, int row, int column, double x)
{
	return cvmSet(a, row, column, x);
}
#endif
class FastHessian {
  
  public:
   
    //! Constructor without image
    FastHessian(std::vector<Ipoint> &ipts, 
                const int octaves = OCTAVES, 
                const int intervals = INTERVALS, 
                const int init_sample = INIT_SAMPLE, 
                const float thres = THRES);

    //! Constructor with image
    FastHessian(IplImage *img, 
                std::vector<Ipoint> &ipts, 
                const int octaves = OCTAVES, 
                const int intervals = INTERVALS, 
                const int init_sample = INIT_SAMPLE, 
                const float thres = THRES);
				
	//! Constructor with image
    FastHessian(IplImage *img,
				IplImage *img_orig2,
                std::vector<Ipoint> &ipts, 
                const int octaves = OCTAVES, 
                const int intervals = INTERVALS, 
                const int init_sample = INIT_SAMPLE, 
                const float thres = THRES);

    //! Destructor
    ~FastHessian();

    //! Save the parameters
    void saveParameters(const int octaves, 
                        const int intervals,
                        const int init_sample, 
                        const float thres);

    //! Set or re-set the integral image source
    void setIntImage(IplImage *img);

    //! Find the image features and write into vector of features
    void getIpoints();
    
  private:

    //---------------- Private Functions -----------------//

    //! Build map of DoH responses
    void buildResponseMap();

    //! Calculate DoH responses for supplied layer
    void buildResponseLayer(ResponseLayer *r);

    //! 3x3x3 Extrema test
    int isExtremum(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b);    
    
    //! Interpolation functions - adapted from Lowe's SIFT implementation
    void interpolateExtremum(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b);
    void interpolateStep(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b,
                          double* xi, double* xr, double* xc );
    CvMat2* deriv3D(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b);
    CvMat2* hessian3D(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b);

    //---------------- Private Variables -----------------//

    //! Pointer to the integral Image, and its attributes 
    IplImage *img;
    int i_width, i_height;
	IplImage *img_orig;

    //! Reference to vector of features passed from outside 
    std::vector<Ipoint> &ipts;

    //! Response stack of determinant of hessian values
    std::vector<ResponseLayer *> responseMap;

    //! Number of Octaves
    int octaves;

    //! Number of Intervals per octave
    int intervals;

    //! Initial sampling step for Ipoint detection
    int init_sample;

    //! Threshold value for blob resonses
    float thresh;
};


#endif