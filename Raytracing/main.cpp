#include <iostream>
#include <limits>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"


const unsigned int width = 1920;
const unsigned int height = 1080;
const unsigned int channels = 3;
const unsigned int samples = 10;

vec3 color(const ray& r, hitable* world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}	
}

hitable* random_scene()
{
	int n = 500;
	hitable** list = new hitable * [n + 1];
	list[0] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(vec3(0.5f, 0.5f, 0.5f)));
	int i = 1;
	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			float choose_mat = random();
			vec3 center(a + 0.9f * random(), 0.2f, b + 0.9f * random());
			if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f)
			{
				if (choose_mat < 0.8f)
				{
					list[i++] = new sphere(center, 0.2f, new lambertian(vec3(random() * random(), random() * random(), random() * random())));
				}
				else if (choose_mat < 0.95f)
				{
					list[i++] = new sphere(center, 0.2f, new metal(vec3(0.5f * (1.0f + random()), 0.5f * (1.0f + random()), 0.5f * (1.0f + random())), 0.5f * random()));
				}
				else
				{
					list[i++] = new sphere(center, 0.2f, new dielectric(1.5f));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5f));
	list[i++] = new sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f));

	return new hitable_list(list, i);
}

int main()
{
	vec3 lookfrom(13.0f, 2.0f, 3.0f);
	vec3 lookat(0.0f, 0.0f, 0.0f);
	float aspect = float(width) / float(height);
	float dist_to_focus = 10.0f;
	float aperture = 0.1f;

	hitable* world = random_scene();
	camera cam(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f), 90.0f / 4.0f, aspect, aperture, dist_to_focus);

	unsigned char* data = new unsigned char[width * height * 3];
	unsigned idx = 0;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			vec3 col(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < samples; ++s)
			{
				float u = float(x + random() - 0.5f) / float(width);
				float v = float(y + random() - 0.5f) / float(height);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(samples);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			data[3 * (y * width + x) + 0] = ir;
			data[3 * (y * width + x) + 1] = ig;
			data[3 * (y * width + x) + 2] = ib;
		}
	}

	stbi_flip_vertically_on_write(true);
	stbi_write_png("output.png", width, height, channels, data, width * channels);

	return 0;
}