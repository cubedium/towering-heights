#ifndef GMA
#define GMA

/** TYPE DEFINITIONS **/
typedef char   i8;
typedef short i16;
typedef int   i32;
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
#define RED    0x001F
#define BLUE  0x7C00
#define GREEN   0x03E0
#define PURPLE 0x7C1F
#define YELLOW 0x03FF
#define CYAN   0x7FE0
#define WHITE  0x7FFF
#define BLACK  0x0000

/** special registers **/
#define DISPCNT *(u16*)0x4000000
#define VBCOUNT *(u16*)0x4000006

/** flags **/
#define VIDMODE5 0x5
#define DISPPAG2 0x10
#define BG3ENABL 0x400

/** miscellaneous **/
#define SCRH 128 
#define SCRW 160

/**** FUNCTIONS ****/
/** init/deinit functions **/
static inline void gma_init()
{
	/*
	 * this function turns on mode 5,
	 * then switches to displaying page 2
	*/

	DISPCNT = (VIDMODE5|DISPPAG2|BG3ENABL);
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
	*/
	while (VBCOUNT<160);
	DISPCNT &=	~DISPPAG2;
	for (int i=0;i<SCRW*SCRH;i++)
	{
		((u16*)PAG2)[i] = ((u16*)PAG1)[i];
	}
	DISPCNT |= DISPPAG2;
}

static inline u16 gma_color(u8 r, u8 g, u8 b)
{
	return r | (g << 5) | (b << 10);
}

static inline void gma_drawRect(u8 x, u8 y, u8 w, u8 h, u16 color)
{
	for (int xx=0;xx<w;xx++)
	{
		for (int yy=0;yy<h;yy++)
		{
			gma_drawPixel(x+xx, y+yy, color);
		}
	}
}

static inline void gma_drawLine(u8 x1, u8 y1, u8 x2, u8 y2, u16 color)
{
	/* traverser*/
	i16 tx = x1 * 16;
	i16 ty = y1 * 16;

	/* movement */
	i16 mx = x2 - x1;
	i16 my = y2 - y1;

	while (tx/16!=x2-1&&ty/16!=y2)
	{
		gma_drawPixel((tx+=mx)/16, (ty+=my)/16, color);		
	}
}

#endif
