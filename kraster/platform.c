#include "kraster/platform.h"
#include "kraster/utility/logger.h"

#include <SDL2/SDL.h>

int kraster_platform_init(struct kraster *kraster, const char *name)
{
	kraster->platform = malloc(sizeof(*kraster->platform));
	if (!kraster->platform) {
		perror("malloc");
		return -1;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		kraster_error("SDL_Init failed");
		free(kraster->platform);
		return -1;
	}

	kraster->platform->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)kraster->width, (int)kraster->height, SDL_WINDOW_BORDERLESS);
	if (!kraster->platform->window) {
		kraster_error("SDL_CreateWindow failed");
		SDL_Quit();
		free(kraster->platform);
		return -1;
	}

	kraster->platform->renderer = SDL_CreateRenderer(kraster->platform->window, -1, 0);
	if (!kraster->platform->renderer) {
		kraster_error("SDL_CreateRenderer failed");
		SDL_DestroyWindow(kraster->platform->window);
		SDL_Quit();
		free(kraster->platform);
		return -1;
	}

	kraster->platform->texture = SDL_CreateTexture(kraster->platform->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, (int)kraster->width, (int)kraster->height);
	if (!kraster->platform->texture) {
		kraster_error("SDL_CreateTexture failed");
		SDL_DestroyRenderer(kraster->platform->renderer);
		SDL_DestroyWindow(kraster->platform->window);
		SDL_Quit();
		free(kraster->platform);
		return -1;
	}

	return 0;
}

void kraster_platform_deinit(struct kraster *kraster)
{
	if (kraster && kraster->platform) {
		SDL_DestroyTexture(kraster->platform->texture);
		SDL_DestroyRenderer(kraster->platform->renderer);
		SDL_DestroyWindow(kraster->platform->window);
		SDL_Quit();
		free(kraster->platform);
	}
}

void kraster_platform_poll(struct kraster *kraster)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_QUIT: {
				kraster->running = false;
				break;
			}
			case SDL_KEYDOWN: {
				if (ev.key.keysym.sym == SDLK_ESCAPE) {
					kraster->running = false;
				}
				break;
			}
		}
	}
}

void kraster_platform_render(struct kraster *kraster)
{
	if (SDL_UpdateTexture(kraster->platform->texture, NULL, kraster->framebuffer, (int)(sizeof(*kraster->framebuffer) * kraster->width)) != 0) {
		kraster_error("SDL_UpdateTexture failed");
		return;
	}

	if (SDL_RenderCopy(kraster->platform->renderer, kraster->platform->texture, NULL, NULL) != 0) {
		kraster_error("SDL_RenderCopy failed");
		return;
	}

	SDL_RenderPresent(kraster->platform->renderer);
}
