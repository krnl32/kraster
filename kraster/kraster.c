#include "kraster/kraster.h"
#include "kraster/platform.h"
#include "kraster/utility/logger.h"

#include <stdio.h>
#include <stdlib.h>

struct kraster *kraster_create(const char *name, uint32_t width, uint32_t height)
{
	struct kraster *kraster = malloc(sizeof(*kraster));
	if (!kraster) {
		perror("malloc");
		return NULL;
	}

	kraster->width = width;
	kraster->height = height;

	if (kraster_platform_init(kraster, name) == -1) {
		kraster_error("kraster_platform_init failed");
		free(kraster);
		return NULL;
	}

	kraster->framebuffer = malloc(sizeof(*kraster->framebuffer) * width * height);
	if (!kraster->framebuffer) {
		perror("malloc");
		kraster_platform_deinit(kraster);
		free(kraster);
		return NULL;
	}

	kraster->running = true;
	return kraster;
}

void kraster_destroy(struct kraster *kraster)
{
	if (kraster) {
		kraster_platform_deinit(kraster);
		free(kraster->framebuffer);
		free(kraster);
	}
}
