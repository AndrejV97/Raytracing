#pragma once

#include "material.h"

class dielectric : public material
{
private:
	float ref_idx;

public:
	dielectric(float ri) : ref_idx(ri) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0f, 1.0f, 1.0f);
		vec3 refracted;

		if (dot(r_in.direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0f / ref_idx;
		}

		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			scattered = ray(rec.p, refracted);
		}
		else
		{
			scattered = ray(rec.p, refracted);
			return false;
		}
		return true;
	}
};