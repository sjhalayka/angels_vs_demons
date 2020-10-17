#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <cstdlib>
#include <GL/glew.h>


#include "primitives.h"
#include "bmp.h"
#include <vector>
#include <complex>
using namespace std;


class toolbar
{
public:

	toolbar(void)
	{

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

	~toolbar(void)
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


	void draw(GLuint ortho_colour_shader_program,
		GLuint ortho_texture_shader_program,
		size_t spacer,
		size_t x, size_t y,
		size_t mouse_x, size_t mouse_y,
		size_t win_width, size_t win_height,
		const vector<string> &names,
		const vector<long long unsigned int>& prices,
		const vector<long long unsigned int>& hp,
		const vector<float>& mass,
		const vector<long long unsigned int>& fish_rate,
		const vector<long long unsigned int> &max_damages,
		const long long unsigned int soul_count,
		size_t selected_box,
		vector<font_character_image> &mimgs)
	{
		y = win_height - y;

		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);

		glUseProgram(ortho_texture_shader_program);

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture_data[0]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		complex<float> v0w;
		complex<float> v1w;
		complex<float> v2w;
		complex<float> v3w;

		complex<float> v0ndc;
		complex<float> v1ndc;
		complex<float> v2ndc;
		complex<float> v3ndc;

		v0w = complex<float>(static_cast<float>(spacer), static_cast<float>(y - this->height));
		v1w = complex<float>(static_cast<float>(spacer), static_cast<float>(y));
		v2w = complex<float>(static_cast<float>(spacer + this->width), static_cast<float>(y));
		v3w = complex<float>(static_cast<float>(spacer + this->width), static_cast<float>(y - this->height));

		v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);

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

		glEnableVertexAttribArray(glGetAttribLocation(ortho_texture_shader_program, "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho_texture_shader_program, "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_texture_shader_program, "texcoord"));
		glVertexAttribPointer(glGetAttribLocation(ortho_texture_shader_program, "texcoord"),
			components_per_tex_coord,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glUniform1i(glGetUniformLocation(ortho_texture_shader_program, "tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		glUseProgram(ortho_colour_shader_program);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glLineWidth(1.0);

		for (size_t i = 2; i < 8; i++)
		{
			if (selected_box == i && prices[i - 2] <= soul_count)
			{
				vertex_3 colour;

				colour.x = 1;
				colour.y = 1;
				colour.z = 1;

				v0w = complex<float>(static_cast<float>(spacer + 64 * i), static_cast<float>(y - 64));
				v1w = complex<float>(static_cast<float>(spacer + 64 * i), static_cast<float>(y));
				v2w = complex<float>(static_cast<float>(spacer + 64 * (i + 1)), static_cast<float>(y));
				v3w = complex<float>(static_cast<float>(spacer + 64 * (i + 1)), static_cast<float>(y - 64));

				v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);

				vector<float> lines;
				lines.push_back(v0ndc.real());
				lines.push_back(v0ndc.imag());
				lines.push_back(0);
				lines.push_back(colour.x);
				lines.push_back(colour.y);
				lines.push_back(colour.z);

				lines.push_back(v1ndc.real());
				lines.push_back(v1ndc.imag());
				lines.push_back(0);
				lines.push_back(colour.x);
				lines.push_back(colour.y);
				lines.push_back(colour.z);

				lines.push_back(v2ndc.real());
				lines.push_back(v2ndc.imag());
				lines.push_back(0);
				lines.push_back(colour.x);
				lines.push_back(colour.y);
				lines.push_back(colour.z);

				lines.push_back(v3ndc.real());
				lines.push_back(v3ndc.imag());
				lines.push_back(0);
				lines.push_back(colour.x);
				lines.push_back(colour.y);
				lines.push_back(colour.z);

				components_per_vertex = 6;
				components_per_position = 3;
				GLuint components_per_colour = 3;

				num_vertices = static_cast<GLuint>(lines.size()) / components_per_vertex;

				glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

				glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(GLfloat), &lines[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(glGetAttribLocation(ortho_colour_shader_program, "position"));
				glVertexAttribPointer(glGetAttribLocation(ortho_colour_shader_program, "position"),
					components_per_position,
					GL_FLOAT,
					GL_FALSE,
					components_per_vertex * sizeof(GLfloat),
					NULL);

				glEnableVertexAttribArray(glGetAttribLocation(ortho_colour_shader_program, "colour"));
				glVertexAttribPointer(glGetAttribLocation(ortho_colour_shader_program, "colour"),
					components_per_colour,
					GL_FLOAT,
					GL_TRUE,
					components_per_vertex * sizeof(GLfloat),
					(const GLvoid*)(components_per_position * sizeof(GLfloat)));

				

				glDrawArrays(GL_LINE_LOOP, 0, num_vertices);
			}
			
			if (prices[i - 2] <= soul_count)
				continue;

			v0w = complex<float>(static_cast<float>(spacer + 64 * i), static_cast<float>(y - 64));
			v1w = complex<float>(static_cast<float>(spacer + 64 * i), static_cast<float>(y));
			v2w = complex<float>(static_cast<float>(spacer + 64 * (i + 1)), static_cast<float>(y));
			v3w = complex<float>(static_cast<float>(spacer + 64 * (i + 1)), static_cast<float>(y - 64));

			v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
			v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
			v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
			v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);

			vector<GLfloat> black_vertex_data = {

				// 3D position, 4D colour coordinate
				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f, // vertex 0
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 2
				v1ndc.real(), v1ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 1
				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 0
				v3ndc.real(), v3ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 3
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f // vertex 2
			};

			components_per_vertex = 7;
			components_per_position = 3;
			GLuint components_per_colour = 4;
			num_vertices = static_cast<GLuint>(black_vertex_data.size()) / components_per_vertex;

			glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

			glBufferData(GL_ARRAY_BUFFER, black_vertex_data.size() * sizeof(GLfloat), &black_vertex_data[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour_shader_program, "position"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour_shader_program, "position"),
				components_per_position,
				GL_FLOAT,
				GL_FALSE,
				components_per_vertex * sizeof(GLfloat),
				NULL);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour_shader_program, "colour"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour_shader_program, "colour"),
				components_per_colour,
				GL_FLOAT,
				GL_TRUE,
				components_per_vertex * sizeof(GLfloat),
				(const GLvoid*)(components_per_position * sizeof(GLfloat)));


	//		glEnable(GL_POLYGON_STIPPLE);

	//		GLubyte halftone[] = {
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
	//0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55 };

	//		glPolygonStipple(halftone);

			glDrawArrays(GL_TRIANGLES, 0, num_vertices);

//			glDisable(GL_POLYGON_STIPPLE);
		}


		glUseProgram(ortho_colour_shader_program);

		bool found_overlay = false;
		vector<string> vs;

		size_t i = 0;

		if (mouse_y < this->height)
		{
			if (mouse_x < spacer + 64)
			{
				//v0w = complex<float>(static_cast<float>(spacer + 64 * 0), static_cast<float>(y - this->height - 64));
				//v1w = complex<float>(static_cast<float>(spacer + 64 * 0), static_cast<float>(y - 64));
				//v2w = complex<float>(static_cast<float>(spacer + 64 * 0 + 256), static_cast<float>(y - 64));
				//v3w = complex<float>(static_cast<float>(spacer + 64 * 0 + 256), static_cast<float>(y - this->height - 64));

				//v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				//v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				//v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				//v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);

				//found_overlay = true;
			}
			else if (mouse_x < spacer + 64 * 2)
			{
				//v0w = complex<float>(static_cast<float>(spacer + 64 * 1), static_cast<float>(y - this->height - 64));
				//v1w = complex<float>(static_cast<float>(spacer + 64 * 1), static_cast<float>(y - 64));
				//v2w = complex<float>(static_cast<float>(spacer + 64 * 1 + 256), static_cast<float>(y - 64));
				//v3w = complex<float>(static_cast<float>(spacer + 64 * 1 + 256), static_cast<float>(y - this->height - 64));

				//v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				//v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				//v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				//v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w); 

				//found_overlay = true;
			}
			else if (mouse_x < spacer + 64 * 3)
			{
				i = 0;

				v0w = complex<float>(static_cast<float>(spacer + 64 * 2), static_cast<float>(y - this->height - 135));
				v1w = complex<float>(static_cast<float>(spacer + 64 * 2), static_cast<float>(y - 64));
				v2w = complex<float>(static_cast<float>(spacer + 64 * 2 + 180), static_cast<float>(y - 64));
				v3w = complex<float>(static_cast<float>(spacer + 64 * 2 + 180), static_cast<float>(y - this->height - 135));

				v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);

				found_overlay = true;
			}
			else if (mouse_x < spacer + 64 * 4)
			{
				i = 1;
				v0w = complex<float>(static_cast<float>(spacer + 64 * 3), static_cast<float>(y - this->height - 135));
				v1w = complex<float>(static_cast<float>(spacer + 64 * 3), static_cast<float>(y - 64));
				v2w = complex<float>(static_cast<float>(spacer + 64 * 3 + 180), static_cast<float>(y - 64));
				v3w = complex<float>(static_cast<float>(spacer + 64 * 3 + 180), static_cast<float>(y - this->height - 135));

				v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);


				found_overlay = true;
				//	g_type = arcangel;
			}
			else if (mouse_x < spacer + 64 * 5)
			{
				i = 2;

				// g_type = angel_boat;

				v0w = complex<float>(static_cast<float>(spacer + 64 * 4), static_cast<float>(y - this->height - 135));
				v1w = complex<float>(static_cast<float>(spacer + 64 * 4), static_cast<float>(y - 64));
				v2w = complex<float>(static_cast<float>(spacer + 64 * 4 + 180), static_cast<float>(y - 64));
				v3w = complex<float>(static_cast<float>(spacer + 64 * 4 + 180), static_cast<float>(y - this->height - 135));

				v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);


				found_overlay = true;
			}
			else if (mouse_x < spacer + 64 * 6)
			{
				i = 3;

				v0w = complex<float>(static_cast<float>(spacer + 64 * 5), static_cast<float>(y - this->height - 135));
				v1w = complex<float>(static_cast<float>(spacer + 64 * 5), static_cast<float>(y - 64));
				v2w = complex<float>(static_cast<float>(spacer + 64 * 5 + 180), static_cast<float>(y - 64));
				v3w = complex<float>(static_cast<float>(spacer + 64 * 5 + 180), static_cast<float>(y - this->height - 135));

				v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);


				found_overlay = true;
				// g_type = arcangel_boat;
			}
			else if (mouse_x < spacer + 64 * 7)
			{
				i = 4;

				v0w = complex<float>(static_cast<float>(spacer + 64 * 6), static_cast<float>(y - this->height - 135));
				v1w = complex<float>(static_cast<float>(spacer + 64 * 6), static_cast<float>(y - 64));
				v2w = complex<float>(static_cast<float>(spacer + 64 * 6 + 180), static_cast<float>(y - 64));
				v3w = complex<float>(static_cast<float>(spacer + 64 * 6 + 180), static_cast<float>(y - this->height - 135));

				v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);

				found_overlay = true;

				// g_type = angel_fortress;
			}
			else if (mouse_x < spacer + 64 * 8)
			{	
				i = 5;
				v0w = complex<float>(static_cast<float>(spacer + 64 * 7), static_cast<float>(y - this->height - 135));
				v1w = complex<float>(static_cast<float>(spacer + 64 * 7), static_cast<float>(y - 64));
				v2w = complex<float>(static_cast<float>(spacer + 64 * 7 + 180), static_cast<float>(y - 64));
				v3w = complex<float>(static_cast<float>(spacer + 64 * 7 + 180), static_cast<float>(y - this->height - 135));

				v0ndc = get_ndc_coords_from_window_coords(win_width, win_height, v0w);
				v1ndc = get_ndc_coords_from_window_coords(win_width, win_height, v1w);
				v2ndc = get_ndc_coords_from_window_coords(win_width, win_height, v2w);
				v3ndc = get_ndc_coords_from_window_coords(win_width, win_height, v3w);


				found_overlay = true;
				//g_type = arcangel_fortress;
			}
		}

		if (found_overlay)
		{
			ostringstream oss;
			oss << names[i];
			vs.push_back(oss.str());
			oss.clear();
			oss.str("");
			oss << "Cost: " << prices[i];
			vs.push_back(oss.str());
			oss.clear();
			oss.str("");
			oss << "HP: " << hp[i];
			vs.push_back(oss.str());
			oss.clear();
			oss.str("");
			oss << "Mass: " << mass[i];
			vs.push_back(oss.str());
			oss.clear();
			oss.str("");
			oss << "Fish rate: " << fish_rate[i];
			vs.push_back(oss.str());
			oss.clear();
			oss.str("");
			oss << "DPS: " << max_damages[i];
			vs.push_back(oss.str());

			vector<GLfloat> popup_vertex_data = {

				// 3D position, 4D colour coordinate
				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f, // vertex 0
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 2
				v1ndc.real(), v1ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 1
				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 0
				v3ndc.real(), v3ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f,// vertex 3
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 0.75f // vertex 2
			};

			components_per_vertex = 7;
			components_per_position = 3;
			GLuint components_per_colour = 4;
			num_vertices = static_cast<GLuint>(popup_vertex_data.size()) / components_per_vertex;

			glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

			glBufferData(GL_ARRAY_BUFFER, popup_vertex_data.size() * sizeof(GLfloat), &popup_vertex_data[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour_shader_program, "position"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour_shader_program, "position"),
				components_per_position,
				GL_FLOAT,
				GL_FALSE,
				components_per_vertex * sizeof(GLfloat),
				NULL);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour_shader_program, "colour"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour_shader_program, "colour"),
				components_per_colour,
				GL_FLOAT,
				GL_TRUE,
				components_per_vertex * sizeof(GLfloat),
				(const GLvoid*)(components_per_position * sizeof(GLfloat)));

			glDrawArrays(GL_TRIANGLES, 0, num_vertices);

			glUseProgram(ortho_texture_shader_program);

			size_t tile_x_pos = static_cast<size_t>(v0w.real()) + 10;
			size_t tile_y_pos = 100;

			for (size_t j = 0; j < vs.size(); j++)
			{
				print_sentence(mimgs, ortho_texture_shader_program, win_width, win_height, tile_x_pos, tile_y_pos, vs[j]);
				tile_y_pos += 20;
			}
		}
	}
};


#endif