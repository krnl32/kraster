#ifndef KRASTER_CAMERA_H
#define KRASTER_CAMERA_H

#include "kraster/math/vector.h"

struct kraster_camera {
	struct kraster_vec3 position;
	struct kraster_vec3 direction;
	struct kraster_vec3 velocity;
	float yaw_rad;
	float pitch_rad;
};

#endif
