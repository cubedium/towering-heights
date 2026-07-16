#ifndef GMA
#define GMA

/** TYPE DEFINITIONS **/
typedef unsigned char   u8;
typedef unsigned short u16;
typedef unsigned int   u32;

/**** DEFINES ****/
/** memory locations **/
#define VRAM 0x06000000
#define PAG1 0x06000000
#define PAG2 0x0600A000

#define IO   0x04000000

/** basic colors **/
#define RED 0x001F

/** special registers **/
#define DISPCNT *(u16*)0x4000000
#define VBCOUNT *(u16*)0x4000006

/** flags **/
#define VIDMODE5 0x5
#define DISPPAG2 0x10
#define BG2ENABL 0x400

/** miscellaneous **/
#define SCRH 160
#define SCRW 128 

/**** FUNCTIONS ****/
/** init/deinit functions **/
static inline void gma_init()
{
	/*
	 * this function turns on mode 5,
	 * then switches to displaying page 2
	*/

	DISPCNT |= (VIDMODE5|DISPPAG2|BG2ENABL);
}

/** graphics functions **/
static inline void gma_drawPixel(u8 x, u8 y, u16 color)
{
	((u16*)PAG1)[x+y*SCRW] = color;
}

static inline void gma_drawPixelIndex(u16 i, u16 color)
{
	((u16*)PAG1)[i] = color;
}

static inline void gma_fillScreen(u16 color)
{
	for (int i=0;i<SCRW*SCRH;i++)
	{
		gma_drawPixelIndex(i, color);
	}
}

static inline void gma_display()
{
	/*
	 * this function first switches to displaying page 1,
	 * then it copies page 1 data to page 2,
	 * and then switches back to displaying page 2,
	 * and finally, waits until it is done rendering
	*/
	DISPCNT &=	~DISPPAG2;
	for (int i=0;i<SCRW*SCRH;i++)
	{
		((u16*)PAG2)[i] = ((u16*)PAG1)[i];
	}
	DISPCNT |= DISPPAG2;
	while (VBCOUNT<160);
}

#endif
