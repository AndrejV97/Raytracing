#pragma once

#include "material.h"
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

class lambertian : public material
{
private:
	vec3 albedo;

public:
	lambertian(const vec3& a) : albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};