#ifndef TEXT_SNIPPET_H
#define TEXT_SNIPPET_H

#include <cstdlib>
#include <GL/glew.h>


#include "primitives.h"

class text_snippet
{
public:
	vertex_3 untransformed_location;
	long signed int y_offset, x_offset;
	string s;

	std::chrono::high_resolution_clock::time_point start_time;

	text_snippet(string s_in)
	{
		y_offset = x_offset = 0;
		s = s_in;
	}

	void cleanup(void)
	{

	}

	~text_snippet(void)
	{
		cleanup();
	}

	bool opengl_init(const BMP& src_bmp)
	{
		cleanup();

		return true;
	}


	void draw(GLuint shader_program, size_t x, size_t y, size_t win_width, size_t win_height)
	{
//		y = win_height - y;

		x += x_offset;
		y += y_offset;

		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - start_time;

		float alpha_max = 255.0f * (1.0f - static_cast<float>(elapsed.count()) / 500.0f);

		float y_offset_max = 30.0f * (static_cast<float>(elapsed.count()) / 500.0f);

		y -= static_cast<size_t>(y_offset_max);

		print_sentence(mimgs, shader_program, win_width, win_height, x, y, s);

	}
};




#endif