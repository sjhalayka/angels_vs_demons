#ifndef SOUL_H
#define SOUL_H

#include <cstdlib>
#include <GL/glew.h>


#include "primitives.h"

class soul
{
public:
	vertex_3 untransformed_location;
	size_t y_offset, x_offset;

	std::chrono::high_resolution_clock::time_point start_time;

	soul(void)
	{
		y_offset = x_offset = 0;
	}

	size_t width = 0;
	size_t height = 0;
	vector<unsigned char> texture_data;

	GLuint tex_handle = 0, vbo_handle = 0;



	void cleanup(void)
	{
		if (glIsTexture(tex_handle))
			glDeleteTextures(1, &tex_handle);

		if (glIsBuffer(vbo_handle))
			glDeleteBuffers(1, &vbo_handle);
	}

	~soul(void)
	{
		cleanup();
	}

	bool opengl_init(const BMP& src_bmp)
	{
		cleanup();

		width = src_bmp.width;
		height = src_bmp.height;
		texture_data = src_bmp.Pixels;

		glGenBuffers(1, &vbo_handle);
		glGenTextures(1, &tex_handle);

		//for (size_t i = 0; i < width; i++)
		//{
		//	for (size_t j = 0; j < height; j++)
		//	{
		//		size_t index = 4 * (j * width + i);

		//		texture_data[index + 3] = texture_data[index + 0];					
		//	}
		//}

		return true;
	}


	void draw(GLuint shader_program, size_t x, size_t y, size_t win_width, size_t win_height)
	{
		y = win_height - y;

		x += x_offset;
		y += y_offset;

		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - start_time;

		float alpha_max = 255.0f * (1.0f - static_cast<float>(elapsed.count()) / 500.0f);

		float y_offset_max = 30.0f * (static_cast<float>(elapsed.count()) / 500.0f);

		y += static_cast<size_t>(y_offset_max);


		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				size_t index = 4 * (j * width + i);

				if (texture_data[index + 3] < alpha_max)
					texture_data[index + 3] = texture_data[index + 0];
				else
					texture_data[index + 3] = static_cast<unsigned char>(alpha_max);
			}
		}


		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture_data[0]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		complex<float> v0w(static_cast<float>(x), static_cast<float>(y));
		complex<float> v1w(static_cast<float>(x), static_cast<float>(y + this->height));
		complex<float> v2w(static_cast<float>(x + this->width), static_cast<float>(y + this->height));
		complex<float> v3w(static_cast<float>(x + this->width), static_cast<float>(y));

		complex<float> v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
		complex<float> v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
		complex<float> v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
		complex<float> v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);

		vector<GLfloat> vertex_data = {

			// 3D position, 2D texture coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1, 0, // vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0, 0, // vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1, 1, // vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1, 0 // vertex 2
		};

		GLuint components_per_vertex = 5;
		GLuint components_per_position = 3;
		GLuint components_per_tex_coord = 2;
		GLuint num_vertices = static_cast<GLuint>(vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(GLfloat), &vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(shader_program, "position"));
		glVertexAttribPointer(glGetAttribLocation(shader_program, "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(shader_program, "texcoord"));
		glVertexAttribPointer(glGetAttribLocation(shader_program, "texcoord"),
			components_per_tex_coord,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glUniform1i(glGetUniformLocation(shader_program, "tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	}
};




#endif