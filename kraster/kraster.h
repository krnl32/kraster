#ifndef KRASTER_H
#define KRASTER_H

#include <stdint.h>
#include <stdbool.h>

struct kraster_platform;

struct kraster {
	struct kraster_platform *platform;
	uint32_t *framebuffer;
	uint32_t width;
	uint32_t height;
	bool running;
};

struct kraster *kraster_create(const char *name, uint32_t width, uint32_t height);
void kraster_destroy(struct kraster *kraster);

#endif
