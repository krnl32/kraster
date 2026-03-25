#include "kraster/kraster.h"
#include "kraster/platform.h"
#include "kraster/render.h"
#include "kraster/utility/logger.h"

int main(void)
{
	struct kraster *kraster = kraster_create("Kraster", 640, 480);
	if (!kraster) {
		kraster_error("kraster_create failed");
		return -1;
	}

	while (kraster->running) {
		kraster_platform_poll(kraster);

		kraster_render_clear(kraster, 0xFF000000);
		kraster_render_grid(kraster, 0xFF242424);
		kraster_render_rect(kraster, 100, 50, 20, 10, 0xFF00FF00);

		kraster_platform_render(kraster);
	}

	kraster_destroy(kraster);
	return 0;
}
