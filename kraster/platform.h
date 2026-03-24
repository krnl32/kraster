#ifndef KRASTER_PLATFORM_H
#define KRASTER_PLATFORM_H

#include "kraster/kraster.h"

struct kraster_platform {
	void *window;
	void *renderer;
	void *texture;
};

int kraster_platform_init(struct kraster *kraster, const char *name);
void kraster_platform_deinit(struct kraster *kraster);
void kraster_platform_poll(struct kraster *kraster);
void kraster_platform_render(struct kraster *kraster);

#endif
