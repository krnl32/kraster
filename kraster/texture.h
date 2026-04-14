#ifndef KRASTER_TEXTURE_H
#define KRASTER_TEXTURE_H

#include <stdint.h>

struct kraster_texture_uv {
	float u;
	float v;
};

struct kraster_texture {
	uint32_t *data;
	int width;
	int height;
};

struct kraster_texture *kraster_texture_load(const char *path);

#endif
