#include "kraster/math/matrix.h"

#include <math.h>

struct kraster_mat4 kraster_mat4_identity(void)
{
	return (struct kraster_mat4){ {
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	} };
}

struct kraster_mat4 kraster_mat4_scale(float sx, float sy, float sz)
{
	return (struct kraster_mat4){ {
		{ sx, 0.0f, 0.0f, 0.0f },
		{ 0.0f, sy, 0.0f, 0.0f },
		{ 0.0f, 0.0f, sz, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	} };
}

struct kraster_mat4 kraster_mat4_translate(float tx, float ty, float tz)
{
	return (struct kraster_mat4){ {
		{ 1.0f, 0.0f, 0.0f, tx },
		{ 0.0f, 1.0f, 0.0f, ty },
		{ 0.0f, 0.0f, 1.0f, tz },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	} };
}

struct kraster_mat4 kraster_mat4_rotate_x(float angle_deg)
{
	float ca = cosf(angle_deg);
	float sa = sinf(angle_deg);

	return (struct kraster_mat4){ {
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, ca, -sa, 0.0f },
		{ 0.0f, sa, ca, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	} };
}

struct kraster_mat4 kraster_mat4_rotate_y(float angle_deg)
{
	float ca = cosf(angle_deg);
	float sa = sinf(angle_deg);

	return (struct kraster_mat4){ {
		{ ca, 0.0f, sa, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ -sa, 0.0f, ca, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	} };
}

struct kraster_mat4 kraster_mat4_rotate_z(float angle_deg)
{
	float ca = cosf(angle_deg);
	float sa = sinf(angle_deg);

	return (struct kraster_mat4){ {
		{ ca, -sa, 0.0f, 0.0f },
		{ sa, ca, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	} };
}

struct kraster_vec4 kraster_mat4_mulv4(struct kraster_mat4 mat, struct kraster_vec4 vec)
{
	struct kraster_vec4 res;
	res.x = (mat.m[0][0] * vec.x) + (mat.m[0][1] * vec.y) + (mat.m[0][2] * vec.z) + (mat.m[0][3] * vec.w);
	res.y = (mat.m[1][0] * vec.x) + (mat.m[1][1] * vec.y) + (mat.m[1][2] * vec.z) + (mat.m[1][3] * vec.w);
	res.z = (mat.m[2][0] * vec.x) + (mat.m[2][1] * vec.y) + (mat.m[2][2] * vec.z) + (mat.m[2][3] * vec.w);
	res.w = (mat.m[3][0] * vec.x) + (mat.m[3][1] * vec.y) + (mat.m[3][2] * vec.z) + (mat.m[3][3] * vec.w);
	return res;
}

struct kraster_mat4 kraster_mat4_mulm4(struct kraster_mat4 mat1, struct kraster_mat4 mat2)
{
	struct kraster_mat4 res;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.m[i][j] = mat1.m[i][0] * mat2.m[0][j] + mat1.m[i][1] * mat2.m[1][j] + mat1.m[i][2] * mat2.m[2][j] + mat1.m[i][3] * mat2.m[3][j];
		}
	}
	return res;
}
