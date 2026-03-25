#include "kraster/math.h"

#include <math.h>

struct kraster_vec3 kraster_vec3_rotate_x(struct kraster_vec3 vec, float angle)
{
	struct kraster_vec3 rotated;
	rotated.x = vec.x;
	rotated.y = vec.y * cosf(angle) - vec.z * sinf(angle);
	rotated.z = vec.y * sinf(angle) + vec.z * cosf(angle);
	return rotated;
}

struct kraster_vec3 kraster_vec3_rotate_y(struct kraster_vec3 vec, float angle)
{
	struct kraster_vec3 rotated;
	rotated.x = vec.x * cosf(angle) - vec.z * sinf(angle);
	rotated.y = vec.y;
	rotated.z = vec.x * sinf(angle) + vec.z * cosf(angle);
	return rotated;
}

struct kraster_vec3 kraster_vec3_rotate_z(struct kraster_vec3 vec, float angle)
{
	struct kraster_vec3 rotated;
	rotated.x = vec.x * cosf(angle) - vec.y * sinf(angle);
	rotated.y = vec.x * sinf(angle) + vec.y * cosf(angle);
	rotated.z = vec.z;
	return rotated;
}
