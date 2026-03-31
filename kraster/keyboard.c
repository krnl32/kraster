#include "kraster/keyboard.h"

#include <SDL2/SDL.h>

bool kraster_keyboard_is_key_down(struct kraster *kraster, enum kraster_keycode key)
{
	(void)kraster;
	const Uint8 *key_states = SDL_GetKeyboardState(NULL);
	return (key < _KRASTER_KEY_COUNT) ? key_states[key] : false;
}
