#include "kraster/render.h"

void kraster_render_clear(struct kraster *kraster, uint32_t color)
{
	for (uint32_t y = 0; y < kraster->height; y++) {
		for (uint32_t x = 0; x < kraster->width; x++) {
			kraster->framebuffer[(kraster->width * y) + x] = color;
		}
	}
}

void kraster_render_grid(struct kraster *kraster)
{
	uint32_t multiples = 10;

	// Horizontally
	for (uint32_t y = 0; y < kraster->height; y += multiples) {
		for (uint32_t x = 0; x < kraster->width; x++) {
			kraster->framebuffer[(kraster->width * y) + x] = 0xFFFFFFFF;
		}
	}

	// Vertically
	for (uint32_t x = 0; x < kraster->width; x += multiples) {
		for (uint32_t y = 0; y < kraster->height; y++) {
			kraster->framebuffer[(kraster->width * y) + x] = 0xFFFFFFFF;
		}
	}
}

void kraster_render_rect(struct kraster *kraster, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color)
{
	for (uint32_t r = y; r < (y + height); r++) {
		for (uint32_t c = x; c < (x + width); c++) {
			kraster->framebuffer[(kraster->width * r) + c] = color;
		}
	}
}
