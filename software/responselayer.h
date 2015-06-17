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

#include <memory.h>
#include <cassert>
#include <sys/mman.h>

//#define RL_DEBUG  // un-comment to test response layer

//#define INPUT_FRAME_ADDR 0x38400000
//#define OUTPUT_FRAME_ADDR 0x3a284800 //Allow 32 Mb for the framebuffer
#define OUTPUT_FRAME_ADDR_9 0x19000000
#define OUTPUT_FRAME_ADDR_15 0x19400000
#define OUTPUT_FRAME_ADDR_21 0x19800000
#define OUTPUT_FRAME_ADDR_27 0x19C00000
#define OUTPUT_FRAME_ADDR_39 0x1A000000
#define OUTPUT_FRAME_ADDR_51 0x1A400000


#define MAP_SIZE 4000000UL
#define MAP_MASK (MAP_SIZE - 1)

extern float* responselayers[6];
extern int responselayers_init;

class ResponseLayer
{
public:

  int width, height, step, filter;
  int img_width, img_height;
  float *responses;
  unsigned char *laplacian;
  
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

  ResponseLayer(int width, int height, int step, int filter)
  {
    assert(width > 0 && height > 0);
    
    this->width = width;
    this->height = height;
    this->step = step;
    this->filter = filter;
	this->img_width = width * step;
	this->img_height = height * step;

    //responses = new float[width*height];
	/*if(responselayers_init < 6)
	{
		if(filter == 9)
		{
			responselayers[0] = (float *)setup_reserved_mem(OUTPUT_FRAME_ADDR_9);
		}
		else if(filter == 15)
		{
			responselayers[1] = (float *)setup_reserved_mem(OUTPUT_FRAME_ADDR_15);
		}
		else if(filter == 21)
		{
			responselayers[2] = (float *)setup_reserved_mem(OUTPUT_FRAME_ADDR_21);
		}
		else if(filter == 27)
		{
			responselayers[3] = (float *)setup_reserved_mem(OUTPUT_FRAME_ADDR_27);
		}
		else if(filter == 39)
		{
			responselayers[4] = (float *)setup_reserved_mem(OUTPUT_FRAME_ADDR_39);
		}
		else if(filter == 51)
		{
			responselayers[5] = (float *)setup_reserved_mem(OUTPUT_FRAME_ADDR_51);
		}
		
		responselayers_init++;
	}

	if(filter == 9)
	{
		responses = responselayers[0];
	}
	else if(filter == 15)
	{
		responses = responselayers[1];
	}
	else if(filter == 21)
	{
		responses = responselayers[2];
	}
	else if(filter == 27)
	{
		responses = responselayers[3];
	}
	else if(filter == 39)
	{
		responses = responselayers[4];
	}
	else if(filter == 51)
	{
		responses = responselayers[5];
	}*/
	
    laplacian = new unsigned char[width*height];

    //memset(responses,0,sizeof(float)*width*height);
	//memset(responses,0,sizeof(float)*img_width*img_height);
    memset(laplacian,0,sizeof(unsigned char)*width*height);
  }

  ~ResponseLayer()
  {
    //if (responses) delete [] responses;
    if (laplacian) delete [] laplacian;
  }

  inline unsigned char getLaplacian(unsigned int row, unsigned int column)
  {
    return laplacian[row * width + column];
  }

  inline unsigned char getLaplacian(unsigned int row, unsigned int column, ResponseLayer *src)
  {
    int scale = this->width / src->width;

    #ifdef RL_DEBUG
    assert(src->getCoords(row, column) == this->getCoords(scale * row, scale * column));
    #endif

    return laplacian[(scale * row) * width + (scale * column)];
  }

  inline float getResponse(unsigned int row, unsigned int column)
  {
    //return responses[row * width + column];
	return responses[row * step * img_width + column * step];
  }

  inline float getResponse(unsigned int row, unsigned int column, ResponseLayer *src)
  {
    int scale = this->width / src->width;

    #ifdef RL_DEBUG
    assert(src->getCoords(row, column) == this->getCoords(scale * row, scale * column));
    #endif

    //return responses[(scale * row) * width + (scale * column)];
	return responses[(scale * row) * step * img_width + (scale * column) * step];
  }

#ifdef RL_DEBUG
  std::vector<std::pair<int, int>> coords;

  inline std::pair<int,int> getCoords(unsigned int row, unsigned int column)
  {
    return coords[row * width + column];
  }

  inline std::pair<int,int> getCoords(unsigned int row, unsigned int column, ResponseLayer *src)
  {
    int scale = this->width / src->width;
    return coords[(scale * row) * width + (scale * column)];
  }
#endif
};
