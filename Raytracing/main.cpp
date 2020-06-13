#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"

int main()
{
	const unsigned int width = 200;
	const unsigned int height = 100;
	const unsigned int channels = 3;

	unsigned char data[width * height * 3];
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			vec3 color(float(x) / float(width), float(y) / float(height), 0.2f);

			int ir = int(255.99f * color[0]);
			int ig = int(255.99f * color[1]);
			int ib = int(255.99f * color[2]);

			data[3 * (y * width + x) + 0] = ir;
			data[3 * (y * width + x) + 1] = ig;
			data[3 * (y * width + x) + 2] = ib;
		}
	}

	stbi_write_png("output.png", width, height, channels, data, width * channels);

	return 0;
}