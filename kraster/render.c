#include "kraster/render.h"
#include "kraster/math/util.h"
#include "kraster/math/vector.h"

#include <stdlib.h>
#include <math.h>

static void kraster_render_triangle_pixel(struct kraster *kraster, struct kraster_vec2 p, struct kraster_vec4 a, struct kraster_vec4 b, struct kraster_vec4 c, uint32_t color);
static void kraster_render_triangle_texel(struct kraster *kraster,
										  struct kraster_vec2 p,
										  struct kraster_vec4 a,
										  struct kraster_vec4 b,
										  struct kraster_vec4 c,
										  struct kraster_texture_uv a_uv,
										  struct kraster_texture_uv b_uv,
										  struct kraster_texture_uv c_uv,
										  struct kraster_texture *texture);
static struct kraster_vec3 barycentric(struct kraster_vec2 p, struct kraster_vec2 a, struct kraster_vec2 b, struct kraster_vec2 c);

void kraster_render_clear_color(struct kraster *kraster, uint32_t color)
{
	for (int y = 0; y < kraster->height; y++) {
		for (int x = 0; x < kraster->width; x++) {
			kraster_render_pixel(kraster, x, y, color);
		}
	}
}

void kraster_render_clear_depth(struct kraster *kraster)
{
	for (int y = 0; y < kraster->height; y++) {
		for (int x = 0; x < kraster->width; x++) {
			kraster->depth_buffer[(kraster->width * y) + x] = 1.0f;
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

void kraster_render_triangle_filled(struct kraster *kraster, int x0, int y0, float z0, float w0, int x1, int y1, float z1, float w1, int x2, int y2, float z2, float w2, uint32_t color)
{
	if (y0 > y1) {
		swapi(&y0, &y1);
		swapi(&x0, &x1);
		swapf(&z0, &z1);
		swapf(&w0, &w1);
	}
	if (y1 > y2) {
		swapi(&y1, &y2);
		swapi(&x1, &x2);
		swapf(&z1, &z2);
		swapf(&w1, &w2);
	}
	if (y0 > y1) {
		swapi(&y0, &y1);
		swapi(&x0, &x1);
		swapf(&z0, &z1);
		swapf(&w0, &w1);
	}

	struct kraster_vec4 a = { (float)x0, (float)y0, z0, w0 };
	struct kraster_vec4 b = { (float)x1, (float)y1, z1, w1 };
	struct kraster_vec4 c = { (float)x2, (float)y2, z2, w2 };

	// Render Flat Bottom
	float left_slope = (y1 != y0) ? (float)(x1 - x0) / (float)abs(y1 - y0) : 0.0f;
	float right_slope = (y2 != y0) ? (float)(x2 - x0) / (float)abs(y2 - y0) : 0.0f;

	if (y1 - y0 != 0) {
		for (int y = y0; y <= y1; y++) {
			int xs = (int)((float)x1 + (float)(y - y1) * left_slope);
			int xe = (int)((float)x0 + (float)(y - y0) * right_slope);

			if (xe < xs) {
				swapi(&xe, &xs);
			}

			for (int x = xs; x < xe; x++) {
				struct kraster_vec2 p = { (float)x, (float)y };
				kraster_render_triangle_pixel(kraster, p, a, b, c, color);
			}
		}
	}

	// Render Flat Top
	left_slope = (y2 != y1) ? (float)(x2 - x1) / (float)abs(y2 - y1) : 0.0f;
	right_slope = (y2 != y0) ? (float)(x2 - x0) / (float)abs(y2 - y0) : 0.0f;

	if (y2 - y1 != 0) {
		for (int y = y1; y <= y2; y++) {
			int xs = (int)((float)x1 + (float)(y - y1) * left_slope);
			int xe = (int)((float)x0 + (float)(y - y0) * right_slope);

			if (xe < xs) {
				swapi(&xe, &xs);
			}

			for (int x = xs; x < xe; x++) {
				struct kraster_vec2 p = { (float)x, (float)y };
				kraster_render_triangle_pixel(kraster, p, a, b, c, color);
			}
		}
	}
}

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
									 struct kraster_texture *texture)
{
	if (y0 > y1) {
		swapi(&y0, &y1);
		swapi(&x0, &x1);
		swapf(&z0, &z1);
		swapf(&w0, &w1);
		swapf(&u0, &u1);
		swapf(&v0, &v1);
	}
	if (y1 > y2) {
		swapi(&y1, &y2);
		swapi(&x1, &x2);
		swapf(&z1, &z2);
		swapf(&w1, &w2);
		swapf(&u1, &u2);
		swapf(&v1, &v2);
	}
	if (y0 > y1) {
		swapi(&y0, &y1);
		swapi(&x0, &x1);
		swapf(&z0, &z1);
		swapf(&w0, &w1);
		swapf(&u0, &u1);
		swapf(&v0, &v1);
	}

	struct kraster_vec4 a = { (float)x0, (float)y0, z0, w0 };
	struct kraster_vec4 b = { (float)x1, (float)y1, z1, w1 };
	struct kraster_vec4 c = { (float)x2, (float)y2, z2, w2 };

	struct kraster_texture_uv a_uv = { u0, v0 };
	struct kraster_texture_uv b_uv = { u1, v1 };
	struct kraster_texture_uv c_uv = { u2, v2 };

	// Render Flat Bottom
	float left_slope = (y1 != y0) ? (float)(x1 - x0) / (float)abs(y1 - y0) : 0.0f;
	float right_slope = (y2 != y0) ? (float)(x2 - x0) / (float)abs(y2 - y0) : 0.0f;

	if (y1 - y0 != 0) {
		for (int y = y0; y <= y1; y++) {
			int xs = (int)((float)x1 + (float)(y - y1) * left_slope);
			int xe = (int)((float)x0 + (float)(y - y0) * right_slope);

			if (xe < xs) {
				swapi(&xe, &xs);
			}

			for (int x = xs; x < xe; x++) {
				struct kraster_vec2 p = { (float)x, (float)y };
				kraster_render_triangle_texel(kraster, p, a, b, c, a_uv, b_uv, c_uv, texture);
			}
		}
	}

	// Render Flat Top
	left_slope = (y2 != y1) ? (float)(x2 - x1) / (float)abs(y2 - y1) : 0.0f;
	right_slope = (y2 != y0) ? (float)(x2 - x0) / (float)abs(y2 - y0) : 0.0f;

	if (y2 - y1 != 0) {
		for (int y = y1; y <= y2; y++) {
			int xs = (int)((float)x1 + (float)(y - y1) * left_slope);
			int xe = (int)((float)x0 + (float)(y - y0) * right_slope);

			if (xe < xs) {
				swapi(&xe, &xs);
			}

			for (int x = xs; x < xe; x++) {
				struct kraster_vec2 p = { (float)x, (float)y };
				kraster_render_triangle_texel(kraster, p, a, b, c, a_uv, b_uv, c_uv, texture);
			}
		}
	}
}

static void kraster_render_triangle_pixel(struct kraster *kraster, struct kraster_vec2 p, struct kraster_vec4 a, struct kraster_vec4 b, struct kraster_vec4 c, uint32_t color)
{
	struct kraster_vec3 weights = barycentric(p, kraster_vec4_to_vec2(a), kraster_vec4_to_vec2(b), kraster_vec4_to_vec2(c));
	float alpha = weights.x;
	float beta = weights.y;
	float gamma = weights.z;

	// interpolation
	float wi = (1 / a.w) * alpha + (1 / b.w) * beta + (1 / c.w) * gamma;
	wi = 1.0f - wi;

	int pixel_loc = (kraster->width * (int)p.y) + (int)p.x;
	if (pixel_loc <= 0 || pixel_loc >= (kraster->width * kraster->height)) {
		return;
	}

	float depth = kraster->depth_buffer[pixel_loc];
	if (wi < depth) {
		kraster_render_pixel(kraster, (int)p.x, (int)p.y, color);
		kraster->depth_buffer[pixel_loc] = wi;
	}
}

static void kraster_render_triangle_texel(struct kraster *kraster,
										  struct kraster_vec2 p,
										  struct kraster_vec4 a,
										  struct kraster_vec4 b,
										  struct kraster_vec4 c,
										  struct kraster_texture_uv a_uv,
										  struct kraster_texture_uv b_uv,
										  struct kraster_texture_uv c_uv,
										  struct kraster_texture *texture)
{
	struct kraster_vec3 weights = barycentric(p, kraster_vec4_to_vec2(a), kraster_vec4_to_vec2(b), kraster_vec4_to_vec2(c));
	float alpha = weights.x;
	float beta = weights.y;
	float gamma = weights.z;

	// interpolation
	float ui = (a_uv.u / a.w) * alpha + (b_uv.u / b.w) * beta + (c_uv.u / c.w) * gamma;
	float vi = (a_uv.v / a.w) * alpha + (b_uv.v / b.w) * beta + (c_uv.v / c.w) * gamma;
	float wi = (1 / a.w) * alpha + (1 / b.w) * beta + (1 / c.w) * gamma;

	ui /= wi;
	vi /= wi;

	// UV -> flip V
	vi = 1.0f - vi;

	// wrap UVs to [0,1) -> REPEAT
	ui = ui - floorf(ui);
	vi = vi - floorf(vi);

	// convert to texture space
	int tx = (int)(ui * (float)texture->width);
	int ty = (int)(vi * (float)texture->height);

	// Clamp
	if (tx >= texture->width) {
		tx = texture->width - 1;
	}
	if (ty >= texture->height) {
		ty = texture->height - 1;
	}

	wi = 1.0f - wi;

	float depth = kraster->depth_buffer[(kraster->width * (int)p.y) + (int)p.x];
	if (wi < depth) {
		kraster_render_pixel(kraster, (int)p.x, (int)p.y, texture->data[(texture->width * ty) + tx]);
		kraster->depth_buffer[(kraster->width * (int)p.y) + (int)p.x] = wi;
	}
}

static struct kraster_vec3 barycentric(struct kraster_vec2 p, struct kraster_vec2 a, struct kraster_vec2 b, struct kraster_vec2 c)
{
	struct kraster_vec2 ac = kraster_vec2_sub(c, a);
	struct kraster_vec2 ab = kraster_vec2_sub(b, a);
	struct kraster_vec2 pc = kraster_vec2_sub(c, p);
	struct kraster_vec2 pb = kraster_vec2_sub(b, p);
	struct kraster_vec2 ap = kraster_vec2_sub(p, a);

	float abc_parallelogram_area = (ac.x * ab.y - ac.y * ab.x);
	float alpha = (pc.x * pb.y - pc.y * pb.x) / abc_parallelogram_area;
	float beta = (ac.x * ap.y - ac.y * ap.x) / abc_parallelogram_area;
	float gamma = 1 - alpha - beta;

	return (struct kraster_vec3){ alpha, beta, gamma };
}
