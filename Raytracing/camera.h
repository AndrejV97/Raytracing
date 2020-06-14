#pragma once

#include "ray.h"
#define _USE_MATH_DEFINES
#include <math.h>

class camera
{
private:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

public:
	camera(float vfov, float aspect)
	{
		float theta = vfov * M_PI / 180.0f;
		float half_height = tan(theta / 2.0f);
		float half_width = aspect * half_height;

		lower_left_corner = vec3(-half_width, -half_height, -1.0f);
		horizontal = vec3(2.0f * half_width, 0.0f, 0.0f);
		vertical = vec3(0.0f, 2.0f * half_height, 0.0f);
		origin = vec3(0.0f, 0.0f, 0.0f);
	}

	ray get_ray(float u, float v)
	{
		return ray(origin, lower_left_corner + u * horizontal + v * vertical);
	}
};
