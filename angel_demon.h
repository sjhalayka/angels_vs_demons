#ifndef ANGEL_DEMON_H
#define ANGEL_DEMON_H

#include <cstdlib>
#include <GL/glew.h>







RGB_uchar HSBtoRGB(unsigned short int hue_degree, unsigned char sat_percent, unsigned char bri_percent)
{
	float R = 0.0f;
	float G = 0.0f;
	float B = 0.0f;

	if (hue_degree > 359)
		hue_degree = 359;

	if (sat_percent > 100)
		sat_percent = 100;

	if (bri_percent > 100)
		bri_percent = 100;

	float hue_pos = 6.0f - ((static_cast<float>(hue_degree) / 359.0f) * 6.0f);

	if (hue_pos >= 0.0f && hue_pos < 1.0f)
	{
		R = 255.0f;
		G = 0.0f;
		B = 255.0f * hue_pos;
	}
	else if (hue_pos >= 1.0f && hue_pos < 2.0f)
	{
		hue_pos -= 1.0f;

		R = 255.0f - (255.0f * hue_pos);
		G = 0.0f;
		B = 255.0f;
	}
	else if (hue_pos >= 2.0f && hue_pos < 3.0f)
	{
		hue_pos -= 2.0f;

		R = 0.0f;
		G = 255.0f * hue_pos;
		B = 255.0f;
	}
	else if (hue_pos >= 3.0f && hue_pos < 4.0f)
	{
		hue_pos -= 3.0f;

		R = 0.0f;
		G = 255.0f;
		B = 255.0f - (255.0f * hue_pos);
	}
	else if (hue_pos >= 4.0f && hue_pos < 5.0f)
	{
		hue_pos -= 4.0f;

		R = 255.0f * hue_pos;
		G = 255.0f;
		B = 0.0f;
	}
	else
	{
		hue_pos -= 5.0f;

		R = 255.0f;
		G = 255.0f - (255.0f * hue_pos);
		B = 0.0f;
	}

	if (100 != sat_percent)
	{
		if (0 == sat_percent)
		{
			R = 255.0f;
			G = 255.0f;
			B = 255.0f;
		}
		else
		{
			if (255.0f != R)
				R += ((255.0f - R) / 100.0f) * (100.0f - sat_percent);
			if (255.0f != G)
				G += ((255.0f - G) / 100.0f) * (100.0f - sat_percent);
			if (255.0f != B)
				B += ((255.0f - B) / 100.0f) * (100.0f - sat_percent);
		}
	}

	if (100 != bri_percent)
	{
		if (0 == bri_percent)
		{
			R = 0.0f;
			G = 0.0f;
			B = 0.0f;
		}
		else
		{
			if (0.0f != R)
				R *= static_cast<float>(bri_percent) / 100.0f;
			if (0.0f != G)
				G *= static_cast<float>(bri_percent) / 100.0f;
			if (0.0f != B)
				B *= static_cast<float>(bri_percent) / 100.0f;
		}
	}

	if (R < 0.0f)
		R = 0.0f;
	else if (R > 255.0f)
		R = 255.0f;

	if (G < 0.0f)
		G = 0.0f;
	else if (G > 255.0f)
		G = 255.0f;

	if (B < 0.0f)
		B = 0.0f;
	else if (B > 255.0f)
		B = 255.0f;

	RGB_uchar rgb;

	rgb.r = static_cast<unsigned char>(R);
	rgb.g = static_cast<unsigned char>(G);
	rgb.b = static_cast<unsigned char>(B);

	return rgb;
}

enum good_type { angel_none, angel, arcangel, angel_boat, arcangel_boat, angel_fortress, arcangel_fortress };

enum bad_type { demon_none, demon, arcdemon, demon_boat, arcdemon_boat, demon_fortress, arcdemon_fortress };

class good_guy
{
public:
	float mass;
	long long signed int hit_points;
	long long unsigned int max_hit_points;
	long long unsigned int max_damage;
	long long unsigned int fish_rate;
	vertex_3 untransformed_location;
	good_type type;

	size_t width;
	size_t height;
	vector<unsigned char> texture_data;

	GLuint tex_handle = 0, vbo_handle = 0;

	std::chrono::high_resolution_clock::time_point start_time;

	good_guy(void)
	{
		start_time = std::chrono::high_resolution_clock::now();
	}

	void cleanup(void)
	{
		if (glIsTexture(tex_handle))
			glDeleteTextures(1, &tex_handle);

		if (glIsBuffer(vbo_handle))
			glDeleteBuffers(1, &vbo_handle);
	}


	~good_guy(void)
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

		return true;
	}

	void draw(GLuint shader_program, size_t x, size_t y, size_t win_width, size_t win_height)
	{
		y = win_height - y;

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		float hp_ratio = static_cast<float>(this->hit_points) / static_cast<float>(this->max_hit_points);

		RGB_uchar rgb = HSBtoRGB(static_cast<unsigned short int>(100.0f*hp_ratio),
			static_cast<unsigned char>(100),
			static_cast<unsigned char>(100));

		for (size_t i = 1; i < width - 1; i++)
		{
			for (size_t j = 1; j < height - 1; j++)
			{
				size_t index = 4 * (j * width + i);

				if (i == 1 || i == 2 || j == 1 || j == 2 || i == width - 2 || j == height - 2 || i == width - 3 || j == height - 3)
				{
					texture_data[index + 0] = rgb.r;
					texture_data[index + 1] = rgb.g;
					texture_data[index + 2] = rgb.b;
					texture_data[index + 3] = 255;
				}
			}
		}

		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - start_time;

		float alpha_max = 255.0f * (static_cast<float>(elapsed.count()) / 500.0f);

		float y_offset_max = 30.0f - 30.0f * (static_cast<float>(elapsed.count()) / 500.0f);

		if (elapsed.count() > 500.0f)
		{
			alpha_max = 255.0f;
			y_offset_max = 0;
		}

		y += static_cast<size_t>(y_offset_max);

		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				size_t index = 4 * (j * width + i);

				texture_data[index + 3] = static_cast<unsigned char>(alpha_max);
			}
		}


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





class bad_guy
{
public:
	float mass;
	long long signed int hit_points;
	long long unsigned int max_hit_points;
	long long unsigned int max_damage;
	long long unsigned int fish_rate;
	vertex_3 untransformed_location;
	bad_type type;

	std::chrono::high_resolution_clock::time_point start_time;

	bad_guy(void)
	{
		start_time = std::chrono::high_resolution_clock::now();
	}


	size_t width;
	size_t height;
	vector<unsigned char> texture_data;

	GLuint tex_handle = 0, vbo_handle = 0;

	void cleanup(void)
	{
		if (glIsTexture(tex_handle))
			glDeleteTextures(1, &tex_handle);

		if (glIsBuffer(vbo_handle))
			glDeleteBuffers(1, &vbo_handle);
	}

	~bad_guy(void)
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

		return true;
	}

	void draw(GLuint shader_program, size_t x, size_t y, size_t win_width, size_t win_height)
	{
		y = win_height - y;

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		float hp_ratio = static_cast<float>(this->hit_points) / static_cast<float>(this->max_hit_points);

		RGB_uchar rgb = HSBtoRGB(static_cast<unsigned short int>(100.0f * hp_ratio),
			static_cast<unsigned char>(100),
			static_cast<unsigned char>(100));

		for (size_t i = 1; i < width - 1; i++)
		{
			for (size_t j = 1; j < height - 1; j++)
			{
				size_t index = 4 * (j * width + i);

				if (i == 1 || i == 2 || j == 1 || j == 2 || i == width - 2 || j == height - 2 || i == width - 3 || j == height - 3)
				{
					texture_data[index + 0] = rgb.r;
					texture_data[index + 1] = rgb.g;
					texture_data[index + 2] = rgb.b;
					texture_data[index + 3] = 255;
				}
			}
		}

		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - start_time;

		float alpha_max = 255.0f * (static_cast<float>(elapsed.count()) / 500.0f);

		float y_offset_max = 30.0f - 30.0f * (static_cast<float>(elapsed.count()) / 500.0f);

		if (elapsed.count() > 500.0f)
		{
			alpha_max = 255.0f;
			y_offset_max = 0;
		}

		y += static_cast<size_t>(y_offset_max);

		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				size_t index = 4 * (j * width + i);

				texture_data[index + 3] = static_cast<unsigned char>(alpha_max);
			}
		}


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