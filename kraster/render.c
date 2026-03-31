#include "kraster/render.h"
#include "kraster/math/util.h"

#include <stdlib.h>
#include <math.h>

static void kraster_render_triangle_filled_flat_bottom(struct kraster *kraster, int x0, int y0, int x1, int y1, int mx, int my, uint32_t color);
static void kraster_render_triangle_filled_flat_top(struct kraster *kraster, int x1, int y1, int mx, int my, int x2, int y2, uint32_t color);

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

void kraster_render_line(struct kraster *kraster, int x0, int y0, int x1, int y1, uint32_t color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	int side_length = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
	float x_inc = (float)dx / (float)side_length;
	float y_inc = (float)dy / (float)side_length;

	float x = (float)x0;
	float y = (float)y0;

	for (int i = 0; i <= side_length; i++) {
		kraster_render_pixel(kraster, (int)roundf(x), (int)roundf(y), color);
		x += x_inc;
		y += y_inc;
	}
}

void kraster_render_triangle(struct kraster *kraster, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	kraster_render_line(kraster, x0, y0, x1, y1, color);
	kraster_render_line(kraster, x1, y1, x2, y2, color);
	kraster_render_line(kraster, x2, y2, x0, y0, color);
}

void kraster_render_triangle_filled(struct kraster *kraster, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	if (y0 > y1) {
		swapi(&y0, &y1);
		swapi(&x0, &x1);
	}
	if (y1 > y2) {
		swapi(&y1, &y2);
		swapi(&x1, &x2);
	}
	if (y0 > y1) {
		swapi(&y0, &y1);
		swapi(&x0, &x1);
	}

	if (y1 == y2) {
		kraster_render_triangle_filled_flat_bottom(kraster, x0, y0, x1, y1, x2, y2, color);
		return;
	}
	if (y0 == y1) {
		kraster_render_triangle_filled_flat_top(kraster, x0, y0, x1, y1, x2, y2, color);
		return;
	}

	int my = y1;
	int mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

	kraster_render_triangle_filled_flat_bottom(kraster, x0, y0, x1, y1, mx, my, color);
	kraster_render_triangle_filled_flat_top(kraster, x1, y1, mx, my, x2, y2, color);
}

static void kraster_render_triangle_filled_flat_bottom(struct kraster *kraster, int x0, int y0, int x1, int y1, int mx, int my, uint32_t color)
{
	float left_slope = (float)(x1 - x0) / (float)(y1 - y0);
	float right_slope = (float)(mx - x0) / (float)(my - y0);

	float xs = (float)x0;
	float xe = (float)x0;

	for (int y = y0; y <= my; y++) {
		kraster_render_line(kraster, (int)xs, y, (int)xe, y, color);
		xs += left_slope;
		xe += right_slope;
	}
}

static void kraster_render_triangle_filled_flat_top(struct kraster *kraster, int x1, int y1, int mx, int my, int x2, int y2, uint32_t color)
{
	float left_slope = (float)(x2 - x1) / (float)(y2 - y1);
	float right_slope = (float)(x2 - mx) / (float)(y2 - my);

	float xs = (float)x2;
	float xe = (float)x2;

	for (int y = y2; y >= y1; y--) {
		kraster_render_line(kraster, (int)xs, y, (int)xe, y, color);
		xs -= left_slope;
		xe -= right_slope;
	}
}
