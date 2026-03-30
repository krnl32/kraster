#ifndef KRASTER_VECTOR_H
#define KRASTER_VECTOR_H

struct kraster_vec2 {
	float x;
	float y;
};

struct kraster_vec3 {
	float x;
	float y;
	float z;
};

struct kraster_vec2 kraster_vec2_add(struct kraster_vec2 vec1, struct kraster_vec2 vec2);
struct kraster_vec2 kraster_vec2_sub(struct kraster_vec2 vec1, struct kraster_vec2 vec2);
struct kraster_vec2 kraster_vec2_mul(struct kraster_vec2 vec, float factor);
struct kraster_vec2 kraster_vec2_div(struct kraster_vec2 vec, float factor);
float kraster_vec2_dot(struct kraster_vec2 vec1, struct kraster_vec2 vec2);
struct kraster_vec2 kraster_vec2_normalize(struct kraster_vec2 vec);
void kraster_vec2_normalize2(struct kraster_vec2 *vec);
float kraster_vec2_length(struct kraster_vec2 vec);

struct kraster_vec3 kraster_vec3_add(struct kraster_vec3 vec1, struct kraster_vec3 vec2);
struct kraster_vec3 kraster_vec3_sub(struct kraster_vec3 vec1, struct kraster_vec3 vec2);
struct kraster_vec3 kraster_vec3_mul(struct kraster_vec3 vec, float factor);
struct kraster_vec3 kraster_vec3_div(struct kraster_vec3 vec, float factor);
struct kraster_vec3 kraster_vec3_cross(struct kraster_vec3 vec1, struct kraster_vec3 vec2);
float kraster_vec3_dot(struct kraster_vec3 vec1, struct kraster_vec3 vec2);
struct kraster_vec3 kraster_vec3_normalize(struct kraster_vec3 vec);
void kraster_vec3_normalize2(struct kraster_vec3 *vec);
float kraster_vec3_length(struct kraster_vec3 vec);

struct kraster_vec3 kraster_vec3_rotate_x(struct kraster_vec3 vec, float angle);
struct kraster_vec3 kraster_vec3_rotate_y(struct kraster_vec3 vec, float angle);
struct kraster_vec3 kraster_vec3_rotate_z(struct kraster_vec3 vec, float angle);

#endif
