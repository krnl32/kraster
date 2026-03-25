#include "kraster/render.h"

void kraster_render_clear(struct kraster *kraster, uint32_t color)
{
	for (int y = 0; y < kraster->height; y++) {
		for (int x = 0; x < kraster->width; x++) {
			kraster_render_pixel(kraster, x, y, color);
		}
	}
}

void kraster_render_grid(struct kraster *kraster, uint32_t color)
{
	int multiples = 10;

	// Horizontally
	for (int y = 0; y < kraster->height; y += multiples) {
		for (int x = 0; x < kraster->width; x++) {
			kraster_render_pixel(kraster, x, y, color);
		}
	}

	// Vertically
	for (int x = 0; x < kraster->width; x += multiples) {
		for (int y = 0; y < kraster->height; y++) {
			kraster_render_pixel(kraster, x, y, color);
		}
	}
}

void kraster_render_rect(struct kraster *kraster, int x, int y, int width, int height, uint32_t color)
{
	for (int r = y; r < (y + height); r++) {
		for (int c = x; c < (x + width); c++) {
			kraster_render_pixel(kraster, c, r, color);
		}
	}
}
