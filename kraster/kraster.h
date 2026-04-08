#ifndef KRASTER_H
#define KRASTER_H

#include <stdint.h>
#include <stdbool.h>

struct kraster_platform;

struct kraster {
	struct kraster_platform *platform;
	uint32_t *framebuffer;
	float *depth_buffer;
	int width;
	int height;
	bool running;
};

struct kraster *kraster_create(const char *name, int width, int height);
void kraster_destroy(struct kraster *kraster);

#endif
