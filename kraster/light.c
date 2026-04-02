#include "kraster/light.h"

#include <math.h>

uint32_t kraster_light_intensity(uint32_t color, float pfactor)
{
	pfactor = fminf(1.0f, fmaxf(0.0f, pfactor));
	uint32_t a = (color & 0xFF000000);
	uint32_t r = (uint32_t)(((float)((color >> 16) & 0xFF)) * pfactor);
	uint32_t g = (uint32_t)(((float)((color >> 8) & 0xFF)) * pfactor);
	uint32_t b = (uint32_t)(((float)((color) & 0xFF)) * pfactor);
	return a | (r << 16) | (g << 8) | b;
}
