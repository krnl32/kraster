#ifndef KRASTER_TRIANGLE_H
#define KRASTER_TRIANGLE_H

#include "kraster/math/vector.h"

#include <stdint.h>

struct kraster_triangle {
	struct kraster_vec2 vertices[3];
	uint32_t color;
};

#endif
