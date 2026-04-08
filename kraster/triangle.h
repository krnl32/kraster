#ifndef KRASTER_TRIANGLE_H
#define KRASTER_TRIANGLE_H

#include "kraster/texture.h"
#include "kraster/math/vector.h"

#include <stdint.h>

struct kraster_triangle {
	struct kraster_vec4 vertices[3];
	struct kraster_texture_uv uvs[3];
	uint32_t color;
	float depth;
};

#endif
