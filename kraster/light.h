#ifndef KRASTER_LIGHT_H
#define KRASTER_LIGHT_H

#include "kraster/math/vector.h"

#include <stdint.h>

struct kraster_light {
	struct kraster_vec3 direction;
};

uint32_t kraster_light_intensity(uint32_t color, float pfactor);

#endif
