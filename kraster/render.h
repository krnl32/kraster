#ifndef KRASTER_RENDER_H
#define KRASTER_RENDER_H

#include "kraster/kraster.h"

#include <assert.h>

void kraster_render_clear(struct kraster *kraster, uint32_t color);
void kraster_render_grid(struct kraster *kraster, uint32_t color);
void kraster_render_rect(struct kraster *kraster, int x, int y, int width, int height, uint32_t color);
void kraster_render_line(struct kraster *kraster, int x0, int y0, int x1, int y1, uint32_t color);
void kraster_render_triangle(struct kraster *kraster, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

static inline void kraster_render_pixel(struct kraster *kraster, int x, int y, uint32_t color)
{
	// assert((x >= 0 && x < kraster->width) && (y >= 0 && y < kraster->height));
	if ((x >= 0 && x < kraster->width) && (y >= 0 && y < kraster->height)) {
		kraster->framebuffer[(kraster->width * y) + x] = color;
	}
}

#endif
