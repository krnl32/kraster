#include "kraster/kraster.h"
#include "kraster/platform.h"
#include "kraster/render.h"
#include "kraster/mesh.h"
#include "kraster/triangle.h"
#include "kraster/keyboard.h"
#include "kraster/light.h"
#include "kraster/camera.h"
#include "kraster/math/vector.h"
#include "kraster/math/matrix.h"
#include "kraster/utility/logger.h"
#include "kraster/utility/timer.h"
#include "kraster/utility/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TRIANGLE_MAX (1024 * 10)
struct kraster_triangle triangles[TRIANGLE_MAX];
size_t triangle_count = 0;

struct kraster_mat4 projection_matrix = { 0 };
struct kraster_mat4 view_matrix = { 0 };

struct kraster_mesh *g_mesh = NULL;

enum kraster_primitive_type primitive_type = KRASTER_TRIANGLE;
enum kraster_render_type render_type = KRASTER_RENDER_TEXTURE;
enum kraster_cull_type cull_type = KRASTER_CULL_BACKFACE;

struct kraster_light global_light = { .direction = { 0, 0, 1 } };

struct kraster_camera camera = { 0 };

static void kraster_on_input(struct kraster *kraster, float dt);
static void kraster_on_update(struct kraster *kraster, float dt);
static void kraster_on_render(struct kraster *kraster, float dt);

int main(int argc, char **argv)
{
	if (argc <= 2) {
		fprintf(stdout, "Usage: %s <cube.obj> <cube.png>\n", argv[0]);
		return 0;
	}

	const char *obj_path = argv[1];
	if (access(obj_path, R_OK) == -1) {
		perror(obj_path);
		return -1;
	}

	const char *texture_path = argv[2];
	if (access(texture_path, R_OK) == -1) {
		perror(texture_path);
		return -1;
	}

	struct kraster *kraster = kraster_create("Kraster", 1280, 720);
	if (!kraster) {
		kraster_error("kraster_create failed");
		return -1;
	}

	// Setup Projection
	float fov = 60.0f * (3.14f / 180.0f);
	float aspect = ((float)kraster->height / (float)kraster->width);
	projection_matrix = kraster_mat4_perspective(fov, aspect, 0.1f, 100.0f);

	// Setup Mesh and Texture
	g_mesh = kraster_mesh_load(obj_path);
	if (g_mesh == NULL) {
		kraster_error("kraster_mesh_load failed");
		return -1;
	}

	g_mesh->rotate = (struct kraster_vec3){ 0, 0, 0 };
	g_mesh->scale = (struct kraster_vec3){ 1.0f, 1.0f, 1.0f };
	g_mesh->translate = (struct kraster_vec3){ 0, 0, 0 };

	g_mesh->texture = kraster_texture_load(texture_path);
	if (g_mesh->texture == NULL) {
		kraster_error("kraster_texture_load failed");
		return -1;
	}

	// Setup Camera
	camera.position = (struct kraster_vec3){ 0, 0, 0 };
	camera.direction = (struct kraster_vec3){ 0, 0, 1 };
	camera.velocity = (struct kraster_vec3){ 0, 0, 0 };
	camera.yaw_rad = 0.0f;
	camera.pitch_rad = 0.0f;

	double last_time = kraster_timer_now_sec();
	int fps = 120;
	double frame_target_time = 1.0 / fps;

	while (kraster->running) {
		double now = kraster_timer_now_sec();

		while ((now - last_time) < frame_target_time) {
			kraster_platform_sleep(kraster, 1);
			now = kraster_timer_now_sec();
		}
		float dt = (float)(now - last_time);
		last_time = now;

		// printf("dt: %.4f (FPS: %.2f)\n", (double)dt, 1.0 / (double)dt);

		kraster_platform_poll(kraster);

		kraster_on_input(kraster, dt);
		kraster_on_update(kraster, dt);
		kraster_on_render(kraster, dt);

		kraster_platform_render(kraster);
	}

	free(g_mesh->texture->data);
	free(g_mesh->texture);
	kraster_destroy(kraster);
	return 0;
}

static void kraster_on_input(struct kraster *kraster, float dt)
{
	// Render Type
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_1)) {
		render_type = KRASTER_RENDER_WIRE;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_2)) {
		render_type = KRASTER_RENDER_WIRE_VERTEX;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_3)) {
		render_type = KRASTER_RENDER_FILL;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_4)) {
		render_type = KRASTER_RENDER_FILL_WIRE;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_5)) {
		render_type = KRASTER_RENDER_TEXTURE;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_6)) {
		render_type = KRASTER_RENDER_TEXTURE_WIRE;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_7)) {
		cull_type = KRASTER_CULL_BACKFACE;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_8)) {
		cull_type = KRASTER_CULL_NONE;
	}

	// Camera Input
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_W)) {
		camera.velocity = kraster_vec3_mul(camera.direction, 5.0f * dt);
		camera.position = kraster_vec3_add(camera.position, camera.velocity);
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_S)) {
		camera.velocity = kraster_vec3_mul(camera.direction, 5.0f * dt);
		camera.position = kraster_vec3_sub(camera.position, camera.velocity);
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_Q)) {
		camera.position.y += 5.0f * dt;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_E)) {
		camera.position.y -= 5.0f * dt;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_Z)) {
		camera.yaw_rad -= 1.0f * dt;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_C)) {
		camera.yaw_rad += 1.0f * dt;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_X)) {
		camera.pitch_rad -= 5.0f * dt;
	}
	if (kraster_keyboard_is_key_down(kraster, KRASTER_KEY_V)) {
		camera.pitch_rad += 5.0f * dt;
	}
}

static void kraster_on_update(struct kraster *kraster, float dt)
{
	float tscalar = 1.0f;
	// g_mesh->rotate.x += 3.1f * dt * tscalar;
	g_mesh->rotate.x = -1.0f;
	g_mesh->rotate.y += 1.1f * dt * tscalar;
	// g_mesh->rotate.z += 2.1f * dt * tscalar;
	g_mesh->translate.z = 5.0f;

	// Setup View Matrix
	struct kraster_vec3 target = { 0, 0, 1 };

	struct kraster_mat4 cam_yaw_rotate = kraster_mat4_rotate_y(camera.yaw_rad);
	struct kraster_mat4 cam_pitch_rotate = kraster_mat4_rotate_x(camera.pitch_rad);
	struct kraster_mat4 cam_rotation = kraster_mat4_identity();
	cam_rotation = kraster_mat4_mulm4(cam_yaw_rotate, cam_rotation);
	cam_rotation = kraster_mat4_mulm4(cam_pitch_rotate, cam_rotation);
	camera.direction = kraster_vec4_to_vec3(kraster_mat4_mulv4(cam_rotation, kraster_vec3_to_vec4(target)));

	target = kraster_vec3_add(camera.position, camera.direction);

	view_matrix = kraster_mat4_look_at(camera.position, target, (struct kraster_vec3){ 0.0f, 1.0f, 0.0f });

	// Setup Transform Matrix
	struct kraster_mat4 scale_matrix = kraster_mat4_scale(g_mesh->scale.x, g_mesh->scale.y, g_mesh->scale.z);

	struct kraster_mat4 rotate_matrix_x = kraster_mat4_rotate_x(g_mesh->rotate.x);
	struct kraster_mat4 rotate_matrix_y = kraster_mat4_rotate_y(g_mesh->rotate.y);
	struct kraster_mat4 rotate_matrix_z = kraster_mat4_rotate_z(g_mesh->rotate.z);

	struct kraster_mat4 translation_matrix = kraster_mat4_translate(g_mesh->translate.x, g_mesh->translate.y, g_mesh->translate.z);

	for (size_t i = 0; i < g_mesh->face_count; i++) {
		struct kraster_face face = g_mesh->faces[i];

		struct kraster_vec3 face_vertices[3];
		face_vertices[0] = g_mesh->vertices[face.x];
		face_vertices[1] = g_mesh->vertices[face.y];
		face_vertices[2] = g_mesh->vertices[face.z];

		struct kraster_vec4 transformed_vertices[3];

		for (int j = 0; j < 3; j++) {
			struct kraster_vec4 transformed_vertex = kraster_vec3_to_vec4(face_vertices[j]);

			struct kraster_mat4 model_matrix = kraster_mat4_identity();
			model_matrix = kraster_mat4_mulm4(scale_matrix, model_matrix);
			model_matrix = kraster_mat4_mulm4(rotate_matrix_z, model_matrix);
			model_matrix = kraster_mat4_mulm4(rotate_matrix_y, model_matrix);
			model_matrix = kraster_mat4_mulm4(rotate_matrix_x, model_matrix);
			model_matrix = kraster_mat4_mulm4(translation_matrix, model_matrix);

			transformed_vertex = kraster_mat4_mulv4(model_matrix, transformed_vertex);

			transformed_vertex = kraster_mat4_mulv4(view_matrix, transformed_vertex);

			transformed_vertices[j] = transformed_vertex;
		}

		// Backface Culling
		struct kraster_vec3 vec_a = kraster_vec4_to_vec3(transformed_vertices[0]);
		struct kraster_vec3 vec_b = kraster_vec4_to_vec3(transformed_vertices[1]);
		struct kraster_vec3 vec_c = kraster_vec4_to_vec3(transformed_vertices[2]);

		struct kraster_vec3 vec_ab = kraster_vec3_sub(vec_b, vec_a);
		kraster_vec3_normalize2(&vec_ab);
		struct kraster_vec3 vec_ac = kraster_vec3_sub(vec_c, vec_a);
		kraster_vec3_normalize2(&vec_ac);
		struct kraster_vec3 normal = kraster_vec3_cross(vec_ab, vec_ac);
		kraster_vec3_normalize2(&normal);

		struct kraster_vec3 origin = { 0, 0, 0 };
		struct kraster_vec3 camera_ray = kraster_vec3_sub(origin, vec_a); // direction from A to CameraPos

		if (cull_type == KRASTER_CULL_BACKFACE) {
			float camera_aligned = kraster_vec3_dot(normal, camera_ray);
			if (camera_aligned < 0) {
				continue;
			}
		}

		// Lightening
		float light_intensity = -kraster_vec3_dot(normal, global_light.direction);
		uint32_t triangle_color = kraster_light_intensity(0xFFFFFFFF, light_intensity);

		// Projection
		struct kraster_triangle projected_triangle;
		projected_triangle.color = triangle_color;
		projected_triangle.uvs[0] = face.x_uv;
		projected_triangle.uvs[1] = face.y_uv;
		projected_triangle.uvs[2] = face.z_uv;

		for (int j = 0; j < 3; j++) {
			struct kraster_vec4 projected_point = kraster_mat4_project(projection_matrix, transformed_vertices[j]);
			projected_point.x *= (float)(kraster->width / 2);
			projected_point.y *= (float)(kraster->height / 2);

			projected_point.y *= -1;

			projected_point.x += (float)(kraster->width / 2);
			projected_point.y += (float)(kraster->height / 2);

			projected_triangle.vertices[j] = projected_point;
		}

		if (triangle_count >= TRIANGLE_MAX) {
			kraster_error("triangle_count out of bounds");
			return;
		}
		triangles[triangle_count++] = projected_triangle;
	}
}

static void kraster_on_render(struct kraster *kraster, float dt)
{
	kraster_render_clear_color(kraster, 0xFF000000);
	kraster_render_clear_depth(kraster);

	for (size_t i = 0; i < triangle_count; i++) {
		struct kraster_triangle triangle = triangles[i];

		if (render_type == KRASTER_RENDER_FILL || render_type == KRASTER_RENDER_FILL_WIRE) {
			kraster_render_triangle_filled(kraster,
										   (int)triangle.vertices[0].x,
										   (int)triangle.vertices[0].y,
										   triangle.vertices[0].z,
										   triangle.vertices[0].w,
										   (int)triangle.vertices[1].x,
										   (int)triangle.vertices[1].y,
										   triangle.vertices[1].z,
										   triangle.vertices[1].w,
										   (int)triangle.vertices[2].x,
										   (int)triangle.vertices[2].y,
										   triangle.vertices[2].z,
										   triangle.vertices[2].w,
										   triangle.color);
		}

		if (render_type == KRASTER_RENDER_TEXTURE || render_type == KRASTER_RENDER_TEXTURE_WIRE) {
			kraster_render_triangle_texture(kraster,
											(int)triangle.vertices[0].x,
											(int)triangle.vertices[0].y,
											triangle.vertices[0].z,
											triangle.vertices[0].w,
											triangle.uvs[0].u,
											triangle.uvs[0].v,
											(int)triangle.vertices[1].x,
											(int)triangle.vertices[1].y,
											triangle.vertices[1].z,
											triangle.vertices[1].w,
											triangle.uvs[1].u,
											triangle.uvs[1].v,
											(int)triangle.vertices[2].x,
											(int)triangle.vertices[2].y,
											triangle.vertices[2].z,
											triangle.vertices[2].w,
											triangle.uvs[2].u,
											triangle.uvs[2].v,
											g_mesh->texture);
		}

		if (render_type == KRASTER_RENDER_WIRE || render_type == KRASTER_RENDER_WIRE_VERTEX || render_type == KRASTER_RENDER_FILL_WIRE || render_type == KRASTER_RENDER_TEXTURE_WIRE) {
			kraster_render_triangle(
				kraster, (int)triangle.vertices[0].x, (int)triangle.vertices[0].y, (int)triangle.vertices[1].x, (int)triangle.vertices[1].y, (int)triangle.vertices[2].x, (int)triangle.vertices[2].y, 0xFFFF0000);
		}

		if (render_type == KRASTER_RENDER_WIRE_VERTEX) {
			kraster_render_rect(kraster, (int)triangle.vertices[0].x, (int)triangle.vertices[0].y, 4, 4, 0xFFFFFF00);
			kraster_render_rect(kraster, (int)triangle.vertices[1].x, (int)triangle.vertices[1].y, 4, 4, 0xFFFFFF00);
			kraster_render_rect(kraster, (int)triangle.vertices[2].x, (int)triangle.vertices[2].y, 4, 4, 0xFFFFFF00);
		}
	}

	triangle_count = 0;
}
