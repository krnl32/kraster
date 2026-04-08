#ifndef KRASTER_RENDER_H
#define KRASTER_RENDER_H

#include "kraster/kraster.h"
#include "kraster/texture.h"

#include <assert.h>

enum kraster_primitive_type {
	KRASTER_TRIANGLE,
};

enum kraster_render_type {
	KRASTER_RENDER_WIRE,
	KRASTER_RENDER_WIRE_VERTEX,
	KRASTER_RENDER_FILL,
	KRASTER_RENDER_FILL_WIRE,
	KRASTER_RENDER_TEXTURE,
	KRASTER_RENDER_TEXTURE_WIRE,
};

enum kraster_cull_type {
	KRASTER_CULL_NONE,
	KRASTER_CULL_BACKFACE,
};

void kraster_render_clear(struct kraster *kraster, uint32_t color);
void kraster_render_grid(struct kraster *kraster, uint32_t color);
void kraster_render_rect(struct kraster *kraster, int x, int y, int width, int height, uint32_t color);
void kraster_render_line(struct kraster *kraster, int x0, int y0, int x1, int y1, uint32_t color);
void kraster_render_triangle(struct kraster *kraster, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void kraster_render_triangle_filled(struct kraster *kraster, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void kraster_render_triangle_texture(struct kraster *kraster,
									 int x0,
									 int y0,
									 float z0,
									 float w0,
									 float u0,
									 float v0,
									 int x1,
									 int y1,
									 float z1,
									 float w1,
									 float u1,
									 float v1,
									 int x2,
									 int y2,
									 float z2,
									 float w2,
									 float u2,
									 float v2,
									 struct kraster_texture *texture);

static inline void kraster_render_pixel(struct kraster *kraster, int x, int y, uint32_t color)
{
	// assert((x >= 0 && x < kraster->width) && (y >= 0 && y < kraster->height));
	if ((x >= 0 && x < kraster->width) && (y >= 0 && y < kraster->height)) {
		kraster->framebuffer[(kraster->width * y) + x] = color;
	}
}

#endif
