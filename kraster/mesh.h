#ifndef KRASTER_MESH_H
#define KRASTER_MESH_H

#include "kraster/math.h"
#include <stddef.h>

#define KRASTER_MESH_VERTEX_MAX 1024
#define KRASTER_MESH_FACE_MAX 1024

struct kraster_face {
	int x;
	int y;
	int z;
};

struct kraster_mesh {
	struct kraster_vec3 vertices[KRASTER_MESH_VERTEX_MAX];
	size_t vertex_count;
	struct kraster_face faces[KRASTER_MESH_FACE_MAX];
	size_t face_count;
	struct kraster_vec3 rotation;
};

#endif
