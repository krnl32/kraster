#ifndef KRASTER_MESH_H
#define KRASTER_MESH_H

#include "kraster/texture.h"
#include "kraster/math/vector.h"

#include <stddef.h>
#include <stdint.h>

#define KRASTER_MESH_VERTEX_MAX (1024 * 10)
#define KRASTER_MESH_FACE_MAX (1024 * 10)

struct kraster_face {
	int x;
	int y;
	int z;
	struct kraster_texture_uv x_uv;
	struct kraster_texture_uv y_uv;
	struct kraster_texture_uv z_uv;
	uint32_t color;
};

struct kraster_mesh {
	struct kraster_vec3 vertices[KRASTER_MESH_VERTEX_MAX];
	size_t vertex_count;
	struct kraster_face faces[KRASTER_MESH_FACE_MAX];
	size_t face_count;

	struct kraster_texture *texture;

	struct kraster_vec3 scale;
	struct kraster_vec3 rotate;
	struct kraster_vec3 translate;
};

struct kraster_mesh *kraster_mesh_load(const char *path);

#endif
