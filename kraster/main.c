#include "kraster/utility/logger.h"

#include <SDL2/SDL.h>

int main(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		kraster_error("SDL_Init failed");
		return -1;
	}

	return 0;
}
