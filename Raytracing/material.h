#pragma once

#include "hitable.h"
#include "util.h"

vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = vec3(random(), random(), random()) - vec3(0.5f, 0.5f, 0.5f);
	} while (p.squared_length() >= 1.0f);
	return p;
}

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};