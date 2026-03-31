#include "kraster/math/vector.h"

#include <math.h>

struct kraster_vec2 kraster_vec2_add(struct kraster_vec2 vec1, struct kraster_vec2 vec2)
{
	return (struct kraster_vec2){ vec1.x + vec2.x, vec1.y + vec2.y };
}

struct kraster_vec2 kraster_vec2_sub(struct kraster_vec2 vec1, struct kraster_vec2 vec2)
{
	return (struct kraster_vec2){ vec1.x - vec2.x, vec1.y - vec2.y };
}

struct kraster_vec2 kraster_vec2_mul(struct kraster_vec2 vec, float factor)
{
	return (struct kraster_vec2){ vec.x * factor, vec.x * factor };
}

struct kraster_vec2 kraster_vec2_div(struct kraster_vec2 vec, float factor)
{
	return (struct kraster_vec2){ vec.x / factor, vec.x / factor };
}

float kraster_vec2_dot(struct kraster_vec2 vec1, struct kraster_vec2 vec2)
{
	return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

struct kraster_vec2 kraster_vec2_normalize(struct kraster_vec2 vec)
{
	float len = kraster_vec2_length(vec);
	return (struct kraster_vec2){ vec.x / len, vec.y / len };
}

void kraster_vec2_normalize2(struct kraster_vec2 *vec)
{
	float len = kraster_vec2_length(*vec);
	vec->x /= len;
	vec->y /= len;
}

float kraster_vec2_length(struct kraster_vec2 vec)
{
	return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

struct kraster_vec3 kraster_vec3_add(struct kraster_vec3 vec1, struct kraster_vec3 vec2)
{
	return (struct kraster_vec3){ vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec1.z };
}

struct kraster_vec3 kraster_vec3_sub(struct kraster_vec3 vec1, struct kraster_vec3 vec2)
{
	return (struct kraster_vec3){ vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z };
}

struct kraster_vec3 kraster_vec3_mul(struct kraster_vec3 vec, float factor)
{
	return (struct kraster_vec3){ vec.x * factor, vec.x * factor, vec.z * factor };
}

struct kraster_vec3 kraster_vec3_div(struct kraster_vec3 vec, float factor)
{
	return (struct kraster_vec3){ vec.x / factor, vec.x / factor, vec.z / factor };
}

struct kraster_vec3 kraster_vec3_cross(struct kraster_vec3 vec1, struct kraster_vec3 vec2)
{
	return (struct kraster_vec3){
		.x = vec1.y * vec2.z - vec1.z * vec2.y,
		.y = vec1.z * vec2.x - vec1.x * vec2.z,
		.z = vec1.x * vec2.y - vec1.y * vec2.x,
	};
}

float kraster_vec3_dot(struct kraster_vec3 vec1, struct kraster_vec3 vec2)
{
	return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

struct kraster_vec3 kraster_vec3_normalize(struct kraster_vec3 vec)
{
	float len = kraster_vec3_length(vec);
	return (struct kraster_vec3){ vec.x / len, vec.y / len, vec.z / len };
}

void kraster_vec3_normalize2(struct kraster_vec3 *vec)
{
	float len = kraster_vec3_length(*vec);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}

float kraster_vec3_length(struct kraster_vec3 vec)
{
	return sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

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

struct kraster_vec4 kraster_vec3_to_vec4(struct kraster_vec3 vec)
{
	return (struct kraster_vec4){ vec.x, vec.y, vec.z, 1.0f };
}

struct kraster_vec3 kraster_vec4_to_vec3(struct kraster_vec4 vec)
{
	return (struct kraster_vec3){ vec.x, vec.y, vec.z };
}
