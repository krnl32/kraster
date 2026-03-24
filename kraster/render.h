#ifndef KRASTER_RENDER_H
#define KRASTER_RENDER_H

#include "kraster/kraster.h"

void kraster_render_clear(struct kraster *kraster, uint32_t color);
void kraster_render_grid(struct kraster *kraster);
void kraster_render_rect(struct kraster *kraster, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);

#endif
