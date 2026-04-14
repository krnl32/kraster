#include "kraster/mesh.h"
#include "utility/logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KRASTER_MESH_UV_MAX (1024 * 10)

struct kraster_mesh *kraster_mesh_load(const char *path)
{
	FILE *fp = fopen(path, "rb");
	if (!fp) {
		perror("fopen");
		return NULL;
	}

	struct kraster_mesh *mesh = malloc(sizeof(*mesh));
	if (!mesh) {
		perror("malloc");
		fclose(fp);
		return NULL;
	}

	memset(mesh, 0, sizeof(*mesh));

	size_t uvs_idx = 0;
	struct kraster_texture_uv *uvs = malloc(sizeof(*uvs) * KRASTER_MESH_UV_MAX);
	if (!uvs) {
		perror("malloc");
		free(mesh);
		fclose(fp);
		return NULL;
	}

	char line[1024];
	while (fgets(line, 1024, fp)) {
		if (!strncmp(line, "v ", 2)) {
			if (mesh->vertex_count >= KRASTER_MESH_VERTEX_MAX) {
				kraster_error("mesh.vertex_count out of bounds");
				free(uvs);
				free(mesh);
				fclose(fp);
				return NULL;
			}

			struct kraster_vec3 vertex;
			sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			mesh->vertices[mesh->vertex_count++] = vertex;
		}

		if (!strncmp(line, "vt ", 3)) {
			if (uvs_idx >= KRASTER_MESH_UV_MAX) {
				kraster_error("uv_idx out of bounds");
				free(uvs);
				free(mesh);
				fclose(fp);
				return NULL;
			}

			struct kraster_texture_uv uv;
			sscanf(line, "vt %f %f", &uv.u, &uv.v);
			uvs[uvs_idx++] = uv;
		}

		if (!strncmp(line, "f ", 2)) {
			int vertex_indices[3];
			int texture_indices[3];
			int normal_indices[3];
			sscanf(line,
				   "f %d/%d/%d %d/%d/%d %d/%d/%d",
				   &vertex_indices[0],
				   &texture_indices[0],
				   &normal_indices[0],
				   &vertex_indices[1],
				   &texture_indices[1],
				   &normal_indices[1],
				   &vertex_indices[2],
				   &texture_indices[2],
				   &normal_indices[2]);

			struct kraster_face face = { .x = vertex_indices[0] - 1,
										 .y = vertex_indices[1] - 1,
										 .z = vertex_indices[2] - 1,
										 .x_uv = uvs[texture_indices[0] - 1],
										 .y_uv = uvs[texture_indices[1] - 1],
										 .z_uv = uvs[texture_indices[2] - 1],
										 .color = 0xFFFFFFFF };
			mesh->faces[mesh->face_count++] = face;
		}
	}

	free(uvs);
	fclose(fp);
	return mesh;
}
