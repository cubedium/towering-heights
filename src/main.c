#include "gma/gma.h"

int main(void)
{
	gma_init();

	gma_fillScreen(RED);

	gma_drawPixel(1, 0, BLUE);
	gma_drawPixel(2, 0, GREEN);
	gma_drawPixel(3, 0, WHITE);
	gma_drawPixel(0, 1, PURPLE);
	gma_drawPixel(1, 1, YELLOW);
	gma_drawPixel(2, 1, CYAN);
	gma_drawPixel(3, 1, BLACK);
	gma_drawRect(4,4,4,4, gma_color(0,31,0));

	gma_display();

}
