#include "kraster/texture.h"
#include "kraster/utility/logger.h"

#include <stb_image.h>

struct kraster_texture *kraster_texture_load(const char *path)
{
	int width, height, channels;
	uint8_t *src = stbi_load(path, &width, &height, &channels, 4);
	if (!src) {
		kraster_error("stbi_load failed");
		return NULL;
	}

	// if (channels != 4) {
	// 	kraster_error("stbi_load invalid format");
	// 	stbi_image_free(src);
	// 	return NULL;
	// }

	size_t size = (size_t)width * (size_t)height * sizeof(uint32_t);
	uint32_t *dst = malloc(size);
	if (!dst) {
		perror("malloc");
		stbi_image_free(src);
		return NULL;
	}

	for (int i = 0; i < width * height; i++) {
		uint8_t r = src[i * 4 + 0];
		uint8_t g = src[i * 4 + 1];
		uint8_t b = src[i * 4 + 2];
		uint8_t a = src[i * 4 + 3];

		dst[i] = (uint32_t)((a << 24) | (b << 16) | (g << 8) | r);
	}

	struct kraster_texture *texture = malloc(sizeof(*texture));
	if (!texture) {
		perror("malloc");
		free(dst);
		stbi_image_free(src);
		return NULL;
	}

	texture->width = width;
	texture->height = height;
	texture->data = dst;

	stbi_image_free(src);
	return texture;
}
