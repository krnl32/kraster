#ifndef KRASTER_MATRIX_H
#define KRASTER_MATRIX_H

#include "kraster/math/vector.h"

struct kraster_mat4 {
	float m[4][4];
};

struct kraster_mat4 kraster_mat4_identity(void);
struct kraster_mat4 kraster_mat4_scale(float sx, float sy, float sz);
struct kraster_mat4 kraster_mat4_translate(float tx, float ty, float tz);
struct kraster_mat4 kraster_mat4_rotate_x(float angle_deg);
struct kraster_mat4 kraster_mat4_rotate_y(float angle_deg);
struct kraster_mat4 kraster_mat4_rotate_z(float angle_deg);

struct kraster_mat4 kraster_mat4_perspective(float fov_rad, float aspect, float znear, float zfar);
struct kraster_vec4 kraster_mat4_project(struct kraster_mat4 projection, struct kraster_vec4 vec);

struct kraster_vec4 kraster_mat4_mulv4(struct kraster_mat4 mat, struct kraster_vec4 vec);
struct kraster_mat4 kraster_mat4_mulm4(struct kraster_mat4 mat1, struct kraster_mat4 mat2);

#endif
