#ifndef KRASTER_MATH_H
#define KRASTER_MATH_H

struct kraster_vec2 {
	float x;
	float y;
};

struct kraster_vec3 {
	float x;
	float y;
	float z;
};

struct kraster_vec3 kraster_vec3_rotate_x(struct kraster_vec3 vec, float angle);
struct kraster_vec3 kraster_vec3_rotate_y(struct kraster_vec3 vec, float angle);
struct kraster_vec3 kraster_vec3_rotate_z(struct kraster_vec3 vec, float angle);

#endif
