#pragma once
#include <iostream>

double random()
{
	return (double)rand() / RAND_MAX;
}

vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = vec3(random(), random(), random()) - vec3(0.5f, 0.5f, 0.5f);
	} while (p.squared_length() >= 1.0f);
	return p;
}

vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		p = vec3(random() - 0.5f, random() - 0.5f, 0.0f);
	} while (dot(p, p) >= 1.0f);

	return p;
}