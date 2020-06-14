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
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect)
	{
		vec3 u, v, w;
		float theta = vfov * M_PI / 180.0f;
		float half_height = tan(theta / 2.0f);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2.0f * half_width * u;
		vertical = 2.0f * half_height * v;
	}

	ray get_ray(float s, float t)
	{
		return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
	}
};
