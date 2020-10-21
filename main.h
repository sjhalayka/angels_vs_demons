#ifndef MAIN_H
#define MAIN_H

#include "dear imgui/imgui.h"
#include "dear imgui/imgui_impl_sdl.h"
#include "dear imgui/imgui_impl_opengl3.h"



#include "primitives.h"
#include "vertex_fragment_shader.h"
#include "matrix_utils.h"
#include "marching_squares.h"
#include "perlin.h"
#include "bmp.h"
#include "font_draw.h"
#include "logging_system.h"
#include "angel_demon.h"
#include "soul.h"
#include "text_snippet.h"
//#include "wave.h"
#include "toolbar.h"
#include "string_utilities.h"
using namespace string_utilities;

#include <complex>
#include <vector>
#include <fstream>
#include <ctime>
#include <map>
#include <forward_list>
#include <list>
#include <chrono>
#include <random>
using namespace std;

#include <cstdlib>
#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "audio.h"

#include <stdio.h>
#include <Windows.h>

#pragma comment(lib, "glew32")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "OpenGL32.lib")





// todo: code signing
// https://ca.godaddy.com/help/signtool-sign-windows-code-with-a-code-signing-certificate-4778
// https://ca.godaddy.com/help/windows-install-codedriver-signing-certificate-and-create-pfx-file-2698
// https://ca.godaddy.com/help/verify-my-certificate-request-code-and-driver-signing-23842


Audio* sound = 0;
Audio* music = 0;


bool parse_levels(const char* const filename);



class level_data
{
public:
	long unsigned int prng_seed;
	long unsigned int level_hint;
	long long unsigned int good_guy_fish_total;
	long long unsigned int bad_guy_fish_total;

	list<good_guy> angels;
	list<bad_guy> demons;
};


vector<level_data> levels;

level_data curr_level;
	

bool developer_mode = false;



int difficulty = 1; 
int max_difficulty = 10;




float player_colour[4] = { 1.0f,0.5f,0.0f,1.0f };
float enemy_colour[4] = { 0.0f,0.5f,1.0f,1.0f };

const unsigned char escape_char = 27;

mt19937 mt_rand(static_cast<unsigned int>(time(0)));

vertex_3 background_colour(1.0f, 0.5, 0.0f);

unsigned int buffer_handle;

vertex_3 camera_pos(0, 0, -1); // Camera position.
vertex_3 look_at_pos(0, 0, 0); // Look at position.

float click_x = 0;
float click_y = 0;

GLint win_x = 800, win_y = 600;

vertex_fragment_shader perspective;
vertex_fragment_shader ortho;
vertex_fragment_shader ortho_colour;

toolbar tb;

const float pi = 4.0f * atanf(1.0f);


bool island_picked = false;
bool sea_picked = false;
bool ui_picked = false;

vector<triangle> untransformed_triangles;
vector<line_segment> untransformed_line_segments;
vector<triangle> untransformed_sea_triangles;

list<soul> souls;
//list<wave> waves;
list<text_snippet> text_snippets;

bool good_guy_mode = true;
good_type g_type = angel_none;
bad_type b_type = demon_none;

float projection_modelview_mat[16];

float z_angle = 0;

float template_width = 0;
float template_height = 0;
float step_size = 0;
float isovalue = 0;
float grid_x_min = 0;
float grid_y_max = 0;

logging_system log_system;

std::chrono::high_resolution_clock::time_point last_refresh_at;
std::chrono::high_resolution_clock::time_point level_started_at;

std::chrono::high_resolution_clock::time_point pause_start = std::chrono::high_resolution_clock::now();
std::chrono::duration<float, std::milli> pause_elapsed = std::chrono::duration<float, std::milli>(pause_start - pause_start);


BMP toolbar_image;

BMP troops_texture_image;
BMP boats_texture_image;
BMP fortresses_texture_image;
BMP soul_texture_image;
//BMP wave_texture_image;

BMP soul_image;
//BMP wave_image;
BMP level_win_image;
BMP level_lose_image;
BMP game_end_image;
BMP splash_screen_image; // Little Red Studio logo 
BMP title_screen_image; // A vs D logo

BMP angel_image;
BMP arcangel_image;
BMP angel_boat_image;
BMP arcangel_boat_image;
BMP angel_fortress_image;
BMP arcangel_fortress_image;
BMP demon_image;
BMP arcdemon_image;
BMP demon_boat_image;
BMP arcdemon_boat_image;
BMP demon_fortress_image;
BMP arcdemon_fortress_image;




long long unsigned int angel_cost = 50;
long long unsigned int arcangel_cost = 250;
long long unsigned int angel_boat_cost = 500;
long long unsigned int arcangel_boat_cost = 2500;
long long unsigned int angel_fortress_cost = 5000;
long long unsigned int arcangel_fortress_cost = 25000;
long long unsigned int demon_cost = 50;
long long unsigned int arcdemon_cost = 250;
long long unsigned int demon_boat_cost = 500;
long long unsigned int arcdemon_boat_cost = 2500;
long long unsigned int demon_fortress_cost = 5000;
long long unsigned int arcdemon_fortress_cost = 25000;


void enable_developer_mode(void)
{
	developer_mode = true;

	angel_cost = 0;
	arcangel_cost = 0;
	angel_boat_cost = 0;
	arcangel_boat_cost = 0;
	angel_fortress_cost = 0;
	arcangel_fortress_cost = 0;
	demon_cost = 0;
	arcdemon_cost = 0;
	demon_boat_cost = 0;
	arcdemon_boat_cost = 0;
	demon_fortress_cost = 0;
	arcdemon_fortress_cost = 0;
}

void disable_developer_mode(void)
{
	developer_mode = false;

	angel_cost = 50;
	arcangel_cost = 250;
	angel_boat_cost = 500;
	arcangel_boat_cost = 2500;
	angel_fortress_cost = 5000;
	arcangel_fortress_cost = 25000;
	demon_cost = 50;
	arcdemon_cost = 250;
	demon_boat_cost = 500;
	arcdemon_boat_cost = 2500;
	demon_fortress_cost = 5000;
	arcdemon_fortress_cost = 25000;
}





long long unsigned int angel_fish_rate = 1;
long long unsigned int arcangel_fish_rate = 5;
long long unsigned int angel_boat_fish_rate = 10;
long long unsigned int arcangel_boat_fish_rate = 50;
long long unsigned int angel_fortress_fish_rate = 100;
long long unsigned int arcangel_fortress_fish_rate = 500;
long long unsigned int demon_fish_rate = 1;
long long unsigned int arcdemon_fish_rate = 5;
long long unsigned int demon_boat_fish_rate = 10;
long long unsigned int arcdemon_boat_fish_rate = 50;
long long unsigned int demon_fortress_fish_rate = 100;
long long unsigned int arcdemon_fortress_fish_rate = 500;

long long unsigned int angel_max_damage = 50;
long long unsigned int arcangel_max_damage = 50;
long long unsigned int angel_boat_max_damage = 50;
long long unsigned int arcangel_boat_max_damage = 50;
long long unsigned int angel_fortress_max_damage = 50;
long long unsigned int arcangel_fortress_max_damage = 50;
long long unsigned int demon_max_damage = 50;
long long unsigned int arcdemon_max_damage = 50;
long long unsigned int demon_boat_max_damage = 50;
long long unsigned int arcdemon_boat_max_damage = 50;
long long unsigned int demon_fortress_max_damage = 50;
long long unsigned int arcdemon_fortress_max_damage = 50;

long long unsigned int angel_max_hit_points = 50;
long long unsigned int arcangel_max_hit_points = 50;
long long unsigned int angel_boat_max_hit_points = 100;
long long unsigned int arcangel_boat_max_hit_points = 100;
long long unsigned int angel_fortress_max_hit_points = 200;
long long unsigned int arcangel_fortress_max_hit_points = 200;
long long unsigned int demon_max_hit_points = 50;
long long unsigned int arcdemon_max_hit_points = 50;
long long unsigned int demon_boat_max_hit_points = 100;
long long unsigned int arcdemon_boat_max_hit_points = 100;
long long unsigned int demon_fortress_max_hit_points = 200;
long long unsigned int arcdemon_fortress_max_hit_points = 200;

float angel_max_mass = 0.01f;
float arcangel_max_mass = 0.01f;
float angel_boat_max_mass = 0.015f;
float arcangel_boat_max_mass = 0.015f;
float angel_fortress_max_mass = 0.02f;
float arcangel_fortress_max_mass = 0.02f;
float demon_max_mass = 0.01f;
float arcdemon_max_mass = 0.01f;
float demon_boat_max_mass = 0.015f;
float arcdemon_boat_max_mass = 0.015f;
float demon_fortress_max_mass = 0.02f;
float arcdemon_fortress_max_mass = 0.02f;

#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))


void rgb2hsv(const unsigned char& src_r, const unsigned char& src_g, const unsigned char& src_b, unsigned char& dst_h, unsigned char& dst_s, unsigned char& dst_v)
{
	float r = src_r / 255.0f;
	float g = src_g / 255.0f;
	float b = src_b / 255.0f;

	float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

	float max = max_f(r, g, b);
	float min = min_f(r, g, b);

	v = max;

	if (max == 0.0f) {
		s = 0;
		h = 0;
	}
	else if (max - min == 0.0f) {
		s = 0;
		h = 0;
	}
	else {
		s = (max - min) / max;

		if (max == r) {
			h = 60 * ((g - b) / (max - min)) + 0;
		}
		else if (max == g) {
			h = 60 * ((b - r) / (max - min)) + 120;
		}
		else {
			h = 60 * ((r - g) / (max - min)) + 240;
		}
	}

	if (h < 0) h += 360.0f;

	dst_h = (unsigned char)(h / 2);   // dst_h : 0-180
	dst_s = (unsigned char)(s * 255); // dst_s : 0-255
	dst_v = (unsigned char)(v * 255); // dst_v : 0-255
}



vector<vertex_3> ortho_collision_island_points;
vector<vertex_3> ortho_collision_sea_points;


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;




#define STATE_LITTLE_RED_SPLASH_SCREEN 0
#define STATE_TITLE_SCREEN 1
#define STATE_GAME 2
#define STATE_PAUSE_SCREEN 3
#define STATE_LEVEL_WIN 4
#define STATE_LEVEL_LOSE 5
#define STATE_GAME_END 6

int state = STATE_LITTLE_RED_SPLASH_SCREEN;


void save_controls_to_disk(const char* const file_name)
{
	ofstream out(file_name);
	out << global_volume << '\n' << difficulty << endl;

	out << player_colour[0] << ' ' << player_colour[1] << ' ' << player_colour[2] << endl;
	out << enemy_colour[0] << ' ' << enemy_colour[1] << ' ' << enemy_colour[2] << endl;



}

void get_controls_from_disk(const char* const file_name)
{
	istringstream iss;

	ifstream in(file_name);

	if (in.fail())
		return;

	string line;

	getline(in, line);
	iss.clear();
	iss.str(line);
	iss >> global_volume;
		
	getline(in, line);
	iss.clear();
	iss.str(line);
	iss >> difficulty;

	getline(in, line);

	string token = " ";
	vector<string> vs = stl_str_tok(token, line);

	if (vs.size() != 3)
		return;

	for (size_t i = 0; i < 3; i++)
	{
		istringstream iss2(vs[i]);
		iss2 >> player_colour[i];
	}


	
	getline(in, line);

	vs = stl_str_tok(token, line);

	if (vs.size() != 3)
		return;

	for (size_t i = 0; i < 3; i++)
	{
		istringstream iss2(vs[i]);
		iss2 >> enemy_colour[i];
	}
}



bool initGL()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(background_colour.x, background_colour.y, background_colour.z, 1);
	glClearDepth(1.0f);

	glViewport(0, 0, win_x, win_y);



	return true;
}


bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "SDL init error", 0);
		return false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

		//Create window
		gWindow = SDL_CreateWindow("Clicker SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_x, win_y, SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

		if (0 == gWindow)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "SDL window creation error", 0);
			return false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);

			if (gContext == NULL)
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "OpenGL create context error", gWindow);
				return false;
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "GLEW init error", gWindow);
					return false;
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "V-sync init error", gWindow);
					return false;
				}

				//Initialize OpenGL
				if (!initGL())
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "OpenGL init error", gWindow);
					return false;
				}
			}
		}
	}


	if (false == perspective.init("media/perspective_colour.vert", "media/perspective_colour.frag"))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load perspective colour shader", gWindow);
		return false;
	}

	if (false == ortho.init("media/ortho_texture.vert", "media/ortho_texture.frag"))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load ortho texture shader", gWindow);
		return false;
	}

	if (false == ortho_colour.init("media/ortho_colour.vert", "media/ortho_colour.frag"))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load ortho colour shader", gWindow);
		return false;
	}

	if (false == init_character_set())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not initialize font", gWindow);
		return false;
	}

	if (false == troops_texture_image.load("media/troops.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load troops.bmp", gWindow);
		return false;
	}

	if (false == boats_texture_image.load("media/boats.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load boats.bmp", gWindow);
		return false;
	}

	if (false == fortresses_texture_image.load("media/fortresses.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load fortresses.bmp", gWindow);
		return false;
	}

	if (false == soul_texture_image.load("media/soul.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load soul.bmp", gWindow);
		return false;
	}

	//if (false == wave_texture_image.load("media/wave.bmp", true))
	//{
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load wave.bmp", gWindow);
	//	return false;
	//}

	if (false == toolbar_image.load("media/toolbar.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load toolbar.bmp", gWindow);
		return false;
	}

	if (false == title_screen_image.load("media/title_screen.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load title_screen.bmp", gWindow);
		return false;
	}

	if (false == splash_screen_image.load("media/little_red_studio.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load little_red_studio.bmp", gWindow);
		return false;
	}

	if (false == level_win_image.load("media/level_win.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load level_win.bmp", gWindow);
		return false;
	}

	if (false == level_lose_image.load("media/level_lose.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load level_lose.bmp", gWindow);
		return false;
	}

	if (false == game_end_image.load("media/game_end.bmp", true))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load game_end.bmp", gWindow);
		return false;
	}


	tb.opengl_init(toolbar_image);

	vector< vector<GLubyte> > tile_data;
	long unsigned int tile_width = 8;
	long unsigned int tile_height = 8;

	slice_tiles(soul_texture_image, tile_data, 1, 8, 8, tile_width, tile_height);

	soul_image.width = tile_width;
	soul_image.height = tile_height;
	soul_image.Pixels = tile_data[0];


	/*


	tile_width = 64;
	tile_height = 64;

	slice_tiles(wave_texture_image, tile_data, 1, 64, 64, tile_width, tile_height);

	wave_image.width = tile_width;
	wave_image.height = tile_height;
	wave_image.Pixels = tile_data[0];
*/





	tile_width = 64;
	tile_height = 64;

	slice_tiles(troops_texture_image, tile_data, 4, 128, 128, tile_width, tile_height);

	angel_image.width = tile_width;
	angel_image.height = tile_height;
	angel_image.Pixels = tile_data[0];

	arcangel_image.width = tile_width;
	arcangel_image.height = tile_height;
	arcangel_image.Pixels = tile_data[1];

	demon_image.width = tile_width;
	demon_image.height = tile_height;
	demon_image.Pixels = tile_data[2];

	arcdemon_image.width = tile_width;
	arcdemon_image.height = tile_height;
	arcdemon_image.Pixels = tile_data[3];


	tile_width = 64;
	tile_height = 64;

	slice_tiles(boats_texture_image, tile_data, 4, 128, 128, tile_width, tile_height);

	angel_boat_image.width = tile_width;
	angel_boat_image.height = tile_height;
	angel_boat_image.Pixels = tile_data[0];

	arcangel_boat_image.width = tile_width;
	arcangel_boat_image.height = tile_height;
	arcangel_boat_image.Pixels = tile_data[1];

	demon_boat_image.width = tile_width;
	demon_boat_image.height = tile_height;
	demon_boat_image.Pixels = tile_data[2];

	arcdemon_boat_image.width = tile_width;
	arcdemon_boat_image.height = tile_height;
	arcdemon_boat_image.Pixels = tile_data[3];




	tile_width = 64;
	tile_height = 64;

	slice_tiles(fortresses_texture_image, tile_data, 4, 128, 128, tile_width, tile_height);

	angel_fortress_image.width = tile_width;
	angel_fortress_image.height = tile_height;
	angel_fortress_image.Pixels = tile_data[0];

	arcangel_fortress_image.width = tile_width;
	arcangel_fortress_image.height = tile_height;
	arcangel_fortress_image.Pixels = tile_data[1];

	demon_fortress_image.width = tile_width;
	demon_fortress_image.height = tile_height;
	demon_fortress_image.Pixels = tile_data[2];

	arcdemon_fortress_image.width = tile_width;
	arcdemon_fortress_image.height = tile_height;
	arcdemon_fortress_image.Pixels = tile_data[3];


	if (false == parse_levels("levels/levels.txt"))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load levels.txt or level data.", gWindow);
		enable_developer_mode();
	}
	else
	{
		disable_developer_mode();
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.WantCaptureMouse = true;


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();


	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(gWindow, gContext);
	ImGui_ImplOpenGL3_Init("#version 400 compatibility");


	get_controls_from_disk("settings.txt");



	initAudio();

	sound = createAudio("media/robot.wav", 0, global_volume);

	if (sound == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load robot.wav", gWindow);
		return false;
	}

	music = createAudio("media/rain.wav", 1, global_volume);

	if (music == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Could not load rain.wav", gWindow);
		return false;
	}

	return true;
}


void close()
{	
	freeAudio(sound);
	freeAudio(music);

	endAudio();
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}



void transform(vertex_3& v)
{
	v.rotate_z(z_angle);
	v.rotate_x(-pi / 3);
	v.z += 0.35f;
}

void untransform(vertex_3& v)
{
	v.z -= 0.35f;
	v.rotate_x(pi / 3);
	v.rotate_z(-z_angle);
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
// http://geomalgorithms.com/a06-_intersect-2.html

bool RayIntersectsTriangle(const vertex_3 rayOrigin,
	const vertex_3 rayVector,
	const vertex_3 v0, const vertex_3 v1, const vertex_3 v2,
	vertex_3& outIntersectionPoint)
{
	const float EPSILON = 0.0000001f;
	vertex_3 vertex0 = v0;// inTriangle->vertex0;
	vertex_3 vertex1 = v1;// inTriangle->vertex1;
	vertex_3 vertex2 = v2;// inTriangle->vertex2;
	vertex_3 edge1, edge2, h, s, q;
	float a, f, u, v;
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0;
	h = rayVector.cross(edge2);
	a = edge1.dot(h);
	if (a > -EPSILON && a < EPSILON)
		return false;    // This ray is parallel to this triangle.
	f = 1.0f / a;
	s = rayOrigin - vertex0;
	u = f * s.dot(h);
	if (u < 0.0f || u > 1.0f)
		return false;
	q = s.cross(edge1);
	v = f * rayVector.dot(q);
	if (v < 0.0f || u + v > 1.0f)
		return false;

	// At this stage we can compute t to find out where the intersection point is on the line.

	float t = f * edge2.dot(q);

	if (t > EPSILON) // ray intersection
	{
		outIntersectionPoint = rayOrigin + rayVector * t;
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}


void get_collision_ortho(float x, float y, bool& island_picked, bool& sea_picked, vertex_3& picked_location)
{
	picked_location.x = 0;
	picked_location.y = 0;
	picked_location.z = 0;

	island_picked = false;
	sea_picked = false;

	vertex_3 cam_pos(x, y, -1);
	vertex_3 look_at_ray(x, y, 1);

	bool found_intersection = false;

	for (size_t i = 0; i < untransformed_triangles.size(); i++)
	{
		vertex_3 v0 = untransformed_triangles[i].vertex[0];
		vertex_3 v1 = untransformed_triangles[i].vertex[1];
		vertex_3 v2 = untransformed_triangles[i].vertex[2];

		vertex_3 outIntersectionPoint;

		found_intersection = RayIntersectsTriangle(cam_pos,
			look_at_ray,
			v0, v1, v2,
			outIntersectionPoint);

		if (found_intersection)
		{
			picked_location = outIntersectionPoint;
			island_picked = true;

			break;
		}
	}

	if (false == found_intersection)
	{
		for (size_t i = 0; i < untransformed_sea_triangles.size(); i++)
		{
			vertex_3 v0 = untransformed_sea_triangles[i].vertex[0];
			vertex_3 v1 = untransformed_sea_triangles[i].vertex[1];
			vertex_3 v2 = untransformed_sea_triangles[i].vertex[2];

			vertex_3 outIntersectionPoint;

			found_intersection = RayIntersectsTriangle(cam_pos,
				look_at_ray,
				v0, v1, v2,
				outIntersectionPoint);

			if (found_intersection)
			{
				picked_location = outIntersectionPoint;
				sea_picked = true;

				break;
			}
		}
	}
}



/*
vertex_3 Get_Screen_Ray(vertex_3 eye, vertex_3 look_at, vertex_3 up, const double fov_degrees, const int x, const int y, const int screen_width, const int screen_height)
{
	vertex_3 E(eye.x, eye.y, eye.z);
	vertex_3 T(look_at.x, look_at.y, look_at.z);
	vertex_3 w(up.x, up.y, up.z);
	w.normalize();

	vertex_3 t = T - E;
	vertex_3 b = w.cross(t);

	vertex_3 t_n = t;
	t_n.normalize();

	vertex_3 b_n = b;
	b_n.normalize();

	vertex_3 v_n = t_n.cross(b_n);

	static const double pi = 4.0 * atan(1.0);

	double theta = fov_degrees * pi / 180.0;
	double d = 1.0;
	double aspect = static_cast<double>(screen_width) / static_cast<double>(screen_height);
	double g_y = -d * tan(theta / 2.0);
	double g_x = g_y * aspect;

	vertex_3 q_x = b_n * (2.0 * g_x) / (static_cast<double>(screen_width) - 1.0);
	vertex_3 q_y = v_n * (2.0 * g_y) / (static_cast<double>(screen_height) - 1.0);

	vertex_3 p_1m = t_n * d - b_n * g_x - v_n * g_y;
	vertex_3 p_ij = p_1m + q_x * x + q_y * y;

	return p_ij;
}
*/


void get_collision_perspective(int x, int y, bool& ui_picked, bool& island_picked, bool& sea_picked, vertex_3& picked_location)
{
	vertex_3 look_at_ray;

	float y_fov_radians = pi / 4.0f; // 45 degrees

	const float aspect = (float)(win_x) / (float)(win_y);
	const float fx = 2.0f * ((float)(x) / (float)(win_x - 1)) - 1.0f;
	const float fy = 2.0f * ((float)(y) / (float)(win_y - 1)) - 1.0f;
	const float tangent = tan(y_fov_radians / 2.0f);
	click_x = -aspect * tangent * fx;
	click_y = -tangent * fy;

	look_at_ray.x = click_x;
	look_at_ray.y = click_y;
	look_at_ray.z = 1;

	bool found_intersection = false;

	if (y < tb.height)
	{
		long long signed int spacer = win_x / 2 - tb.width / 2;

		if (spacer < 0)
			spacer = 0;

		if (x >= spacer && x < spacer + tb.width)
		{
			found_intersection = true;
			ui_picked = true;
			picked_location.x = static_cast<float>(x);
			picked_location.y = static_cast<float>(y);
			picked_location.z = 0;
		}
	}

	if (false == found_intersection)
	{
		for (size_t i = 0; i < untransformed_triangles.size(); i++)
		{
			vertex_3 v0 = untransformed_triangles[i].vertex[0];
			vertex_3 v1 = untransformed_triangles[i].vertex[1];
			vertex_3 v2 = untransformed_triangles[i].vertex[2];
			transform(v0);
			transform(v1);
			transform(v2);

			vertex_3 outIntersectionPoint;

			found_intersection = RayIntersectsTriangle(camera_pos,
				look_at_ray,
				v0, v1, v2,
				outIntersectionPoint);

			if (found_intersection)
			{
				picked_location = outIntersectionPoint;
				untransform(picked_location);

				island_picked = true;
				break;
			}
		}

		if (false == found_intersection)
		{
			for (size_t i = 0; i < untransformed_sea_triangles.size(); i++)
			{
				vertex_3 v0 = untransformed_sea_triangles[i].vertex[0];
				vertex_3 v1 = untransformed_sea_triangles[i].vertex[1];
				vertex_3 v2 = untransformed_sea_triangles[i].vertex[2];

				transform(v0);
				transform(v1);
				transform(v2);

				vertex_3 outIntersectionPoint;

				found_intersection = RayIntersectsTriangle(camera_pos,
					look_at_ray,
					v0, v1, v2,
					outIntersectionPoint);

				if (found_intersection)
				{
					picked_location = outIntersectionPoint;
					untransform(picked_location);

					sea_picked = true;

					break;
				}
			}
		}
	}
}


void init_level(bool clear_angels_and_demons)
{
	untransformed_triangles.clear();
	untransformed_line_segments.clear();
	untransformed_sea_triangles.clear();

	if (clear_angels_and_demons)
	{
		curr_level.angels.clear();
		curr_level.demons.clear();
	}

	souls.clear();
	//waves.clear();
	ortho_collision_island_points.clear();
	ortho_collision_sea_points.clear();

	// Image height is equal to image width
	size_t image_width = 20;

	template_width = 1.25;
	step_size = template_width / static_cast<float>(image_width - 1);
	template_height = step_size * (image_width - 1);

	isovalue = 0.0f;

	grid_x_min = -template_width / 2.0f;
	grid_y_max = template_height / 2.0f;

	// Generate geometric primitives using marching squares.
	grid_square g;

	float grid_x_pos = grid_x_min; // Start at minimum x.
	float grid_y_pos = grid_y_max; // Start at maximum y.

	mt_rand.seed(curr_level.prng_seed);
	perlin perlin_noise(mt_rand);

	// Begin march.
	for (short unsigned int y = 0; y < image_width - 1; y++, grid_y_pos -= step_size, grid_x_pos = grid_x_min)
	{
		for (short unsigned int x = 0; x < image_width - 1; x++, grid_x_pos += step_size)
		{
			g.vertex[0] = vertex_3(grid_x_pos, grid_y_pos, 0);
			g.vertex[1] = vertex_3(grid_x_pos, grid_y_pos - step_size, 0);
			g.vertex[2] = vertex_3(grid_x_pos + step_size, grid_y_pos - step_size, 0);
			g.vertex[3] = vertex_3(grid_x_pos + step_size, grid_y_pos, 0);

			float noise0 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[0].x, g.vertex[0].y, 2.0, 2.0, 20));
			float noise1 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[1].x, g.vertex[1].y, 2.0, 2.0, 20));
			float noise2 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[2].x, g.vertex[2].y, 2.0, 2.0, 20));
			float noise3 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[3].x, g.vertex[3].y, 2.0, 2.0, 20));

			float noise4 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[0].x + 100, g.vertex[0].y + 100, 2.0, 2.0, 20));
			float noise5 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[1].x + 100, g.vertex[1].y + 100, 2.0, 2.0, 20));
			float noise6 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[2].x + 100, g.vertex[2].y + 100, 2.0, 2.0, 20));
			float noise7 = static_cast<float>(perlin_noise.PerlinNoise2D(g.vertex[3].x + 100, g.vertex[3].y + 100, 2.0, 2.0, 20));

			if (noise4 > 0)
				noise0 = noise4;

			if (noise5 > 0)
				noise1 = noise5;

			if (noise6 > 0)
				noise2 = noise6;

			if (noise7 > 0)
				noise3 = noise7;


			if (y == 0)
			{
				g.value[0] = -1.0f;
				g.value[3] = -1.0f;
			}
			else
			{
				g.value[0] = noise0;
				g.value[3] = noise3;
			}

			if (y == image_width - 2)
			{
				g.value[1] = -1.0f;
				g.value[2] = -1.0f;
			}
			else
			{
				g.value[1] = noise1;
				g.value[2] = noise2;
			}

			if (x == 0)
			{
				g.value[0] = -1.0f;
				g.value[1] = -1.0f;
			}

			if (x == image_width - 2)
			{
				g.value[2] = -1.0f;
				g.value[3] = -1.0f;
			}

			g.generate_primitives(untransformed_line_segments, untransformed_triangles, isovalue);
		}
	}


	for (size_t i = 0; i < untransformed_triangles.size(); i++)
	{
		vertex_3 temp = untransformed_triangles[i].vertex[0];
		untransformed_triangles[i].vertex[0] = untransformed_triangles[i].vertex[2];
		untransformed_triangles[i].vertex[2] = temp;
	}

	image_width = 50;

	template_width = 50;
	step_size = template_width / static_cast<float>(image_width - 1);
	template_height = step_size * (image_width - 1);

	isovalue = 0.0;

	grid_x_min = -template_width / 2.0f;
	grid_y_max = template_height / 2.0f;

	grid_x_pos = grid_x_min; // Start at minimum x.
	grid_y_pos = grid_y_max; // Start at maximum y.


	// Begin march.
	for (short unsigned int y = 0; y < image_width - 1; y++, grid_y_pos -= step_size, grid_x_pos = grid_x_min)
	{
		for (short unsigned int x = 0; x < image_width - 1; x++, grid_x_pos += step_size)
		{
			g.vertex[0] = vertex_3(grid_x_pos, grid_y_pos, 0);
			g.vertex[1] = vertex_3(grid_x_pos, grid_y_pos - step_size, 0);
			g.vertex[2] = vertex_3(grid_x_pos + step_size, grid_y_pos - step_size, 0);
			g.vertex[3] = vertex_3(grid_x_pos + step_size, grid_y_pos, 0);

			g.value[0] = 1;
			g.value[1] = 1;
			g.value[2] = 1;
			g.value[3] = 1;

			vector<line_segment> ls;

			g.generate_primitives(ls, untransformed_sea_triangles, isovalue);
		}
	}

	for (size_t i = 0; i < untransformed_sea_triangles.size(); i++)
	{
		vertex_3 temp = untransformed_sea_triangles[i].vertex[0];
		untransformed_sea_triangles[i].vertex[0] = untransformed_sea_triangles[i].vertex[2];
		untransformed_sea_triangles[i].vertex[2] = temp;
	}


	while (ortho_collision_island_points.size() < 100 || ortho_collision_sea_points.size() < 100)
	{
		vertex_3 picked_location;

		float x_pos = static_cast<float>(mt_rand()) / static_cast<float>(static_cast<long unsigned int>(-1));
		float y_pos = static_cast<float>(mt_rand()) / static_cast<float>(static_cast<long unsigned int>(-1));

		x_pos *= 2.0f;
		x_pos -= 1.0f;
		x_pos *= 0.5f;

		y_pos *= 2.0f;
		y_pos -= 1.0f;
		y_pos *= 0.5f;

		get_collision_ortho(x_pos, y_pos, island_picked, sea_picked, picked_location);

		if (island_picked && ortho_collision_island_points.size() < 100)
		{
			if (picked_location.length() < 1.0f)
				ortho_collision_island_points.push_back(picked_location);
		}
		else if (sea_picked && ortho_collision_sea_points.size() < 100)
		{
			if (picked_location.length() < 1.0f)
			{
				ortho_collision_sea_points.push_back(picked_location);

				//float time_offset = 1000.0f*(static_cast<float>(mt_rand()) / static_cast<float>(static_cast<long unsigned int>(-1)));


				//wave w;
				//w.opengl_init(wave_image);
				//w.x_offset = 0;
				//w.y_offset = 0;
				//w.untransformed_location = picked_location;
				//w.start_time = std::chrono::high_resolution_clock::now();
				//w.start_time += std::chrono::milliseconds(static_cast<long unsigned int>(time_offset));
				//waves.push_front(w);
			}
		}
	}

	level_started_at = std::chrono::high_resolution_clock::now();
	last_refresh_at = level_started_at;
}





float add_vel(float a, float b)
{
	if (a > 1)
		a = 1;

	if (b > 1)
		b = 1;

	return (a + b) / (1.0f + a * b);
}

void game_idle_func(void)
{
	if (developer_mode)
		return;

	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> elapsed = end_time - last_refresh_at;

	if (elapsed.count() >= 1000.0f)
	{
		last_refresh_at = end_time;

		size_t chance = (max_difficulty + 1) - difficulty;
		chance = chance * chance;

		curr_level.bad_guy_fish_total += difficulty;


		for (size_t i = 0; i < 1 /*num_rain_picks*/; i++)
		{
			if (mt_rand() % chance == 0)
			{
				size_t selection = (mt_rand() % 6) + 1;
				bad_type b_type;

				if (selection == 1)
					b_type = demon;
				else if (selection == 2)
					b_type = arcdemon;
				else if (selection == 3)
					b_type = demon_boat;
				else if (selection == 4)
					b_type = arcdemon_boat;
				else if (selection == 5)
					b_type = demon_fortress;
				else if (selection == 6)
					b_type = arcdemon_fortress;


				vertex_3 picked_location;
				
				if(b_type == demon_boat || b_type == arcdemon_boat)
					picked_location = ortho_collision_sea_points[mt_rand() % ortho_collision_sea_points.size()]; 
				else
					picked_location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];

				if (b_type == demon && curr_level.bad_guy_fish_total >= demon_cost)
				{
					bad_guy a;
					a.mass = demon_max_mass;
					a.hit_points = a.max_hit_points = demon_max_hit_points;
					a.untransformed_location = picked_location;
					a.max_damage = demon_max_damage;
					a.type = demon;
					a.fish_rate = demon_fish_rate;
					a.start_time = std::chrono::high_resolution_clock::now();
					a.opengl_init(demon_image);

					curr_level.demons.push_back(a);

					curr_level.bad_guy_fish_total -= demon_cost;
				}
				else if (b_type == arcdemon && curr_level.bad_guy_fish_total >= arcdemon_cost)
				{
					bad_guy a;
					a.mass = arcdemon_max_mass;
					a.hit_points = a.max_hit_points = arcdemon_max_hit_points;
					a.untransformed_location = picked_location;
					a.max_damage = arcdemon_max_damage;
					a.type = arcdemon;
					a.fish_rate = arcdemon_fish_rate;
					a.start_time = std::chrono::high_resolution_clock::now();
					a.opengl_init(arcdemon_image);

					curr_level.demons.push_back(a);

					curr_level.bad_guy_fish_total -= arcdemon_cost;
				}
				else if (b_type == demon_boat && curr_level.bad_guy_fish_total >= demon_boat_cost)
				{
					bad_guy a;
					a.mass = demon_boat_max_mass;
					a.hit_points = a.max_hit_points = demon_boat_max_hit_points;
					a.untransformed_location = picked_location;
					a.max_damage = demon_boat_max_damage;
					a.type = demon_boat;
					a.fish_rate = demon_boat_fish_rate;
					a.start_time = std::chrono::high_resolution_clock::now();
					a.opengl_init(demon_boat_image);

					curr_level.demons.push_back(a);

					curr_level.bad_guy_fish_total -= demon_boat_cost;
				}
				else if (b_type == arcdemon_boat && curr_level.bad_guy_fish_total >= arcdemon_boat_cost)
				{
					bad_guy a;
					a.mass = arcdemon_boat_max_mass;
					a.hit_points = a.max_hit_points = arcdemon_boat_max_hit_points;
					a.untransformed_location = picked_location;
					a.max_damage = arcdemon_boat_max_damage;
					a.type = arcdemon_boat;
					a.fish_rate = arcdemon_boat_fish_rate;
					a.start_time = std::chrono::high_resolution_clock::now();
					a.opengl_init(arcdemon_boat_image);

					curr_level.demons.push_back(a);

					curr_level.bad_guy_fish_total -= arcdemon_boat_cost;
				}
				else if (b_type == demon_fortress && curr_level.bad_guy_fish_total >= demon_fortress_cost)
				{
					bad_guy a;
					a.mass = demon_fortress_max_mass;
					a.hit_points = a.max_hit_points = demon_fortress_max_hit_points;
					a.untransformed_location = picked_location;
					a.max_damage = demon_fortress_max_damage;
					a.type = demon_fortress;
					a.fish_rate = demon_fortress_fish_rate;
					a.start_time = std::chrono::high_resolution_clock::now();
					a.opengl_init(demon_fortress_image);

					curr_level.demons.push_back(a);

					curr_level.bad_guy_fish_total -= demon_fortress_cost;
				}
				else if (b_type == arcdemon_fortress && curr_level.bad_guy_fish_total >= arcdemon_fortress_cost)
				{
					bad_guy a;
					a.mass = arcdemon_fortress_max_mass;
					a.hit_points = a.max_hit_points = arcdemon_fortress_max_hit_points;
					a.untransformed_location = picked_location;
					a.max_damage = arcdemon_fortress_max_damage;
					a.type = arcdemon_fortress;
					a.fish_rate = arcdemon_fortress_fish_rate;
					a.start_time = std::chrono::high_resolution_clock::now();
					a.opengl_init(arcdemon_fortress_image);

					curr_level.demons.push_back(a);

					curr_level.bad_guy_fish_total -= arcdemon_fortress_cost;
				}


			}
		}


		// Get angel damage
		for (auto i = curr_level.angels.begin(); i != curr_level.angels.end();)
		{
			vertex_3 v = i->untransformed_location;
			transform(v);

			float U = 0;
			float avg_max_damage = 0;

			for (auto j = curr_level.demons.begin(); j != curr_level.demons.end(); j++)
			{
				vertex_3 l = j->untransformed_location;
				transform(l);

				vertex_3 ray = v - l;

				float distance = ray.length();

				if (distance == 0)
					distance = 0.0000001f;

				U = add_vel(U, pow(j->mass / distance, 0.5f));

				avg_max_damage += j->max_damage;
			}

			float t = sqrtf(1.0f - U * U);

			if (curr_level.demons.size() == 0)
				avg_max_damage = 0;
			else
				avg_max_damage /= curr_level.demons.size();

			float y = static_cast<float>(mt_rand()) / static_cast<float>(static_cast<long unsigned int>(-1));

			long long signed int damage = static_cast<long signed int>(round(avg_max_damage * (1.0f - t) * y));

			if (damage > 0)
			{
				ostringstream oss;
				oss << "-" << damage;

				text_snippet ts(oss.str());
				ts.untransformed_location = i->untransformed_location;
				ts.start_time = std::chrono::high_resolution_clock::now();
				ts.x_offset = 32 - static_cast<long signed int>(get_sentence_width(mimgs, oss.str())/2);
				ts.y_offset = -48;
				text_snippets.push_back(ts);
			}

			if (false == developer_mode)
				i->hit_points -= damage;

			if (i->hit_points <= 0)
			{
				i = curr_level.angels.erase(i);

				if (curr_level.angels.size() == 0)
				{
					state = STATE_LEVEL_LOSE;
					return;
				}
			}
			else
			{
				// do fishing here
				if (t == 0)
					t = 0.0000001f;

				long unsigned int x = static_cast<long unsigned int>(1.0f / t);

				if (0 == mt_rand() % x)
				{
					curr_level.good_guy_fish_total += i->fish_rate;

					soul s;
					s.opengl_init(soul_image);

					if (i->type == angel || i->type == arcangel)
					{
						s.x_offset = 32 - 8 / 2;
						s.y_offset = 64;
					}
					else if (i->type == angel_boat || i->type == arcangel_boat)
					{
						s.x_offset = 32 - 8 / 2;
						s.y_offset = 64;
					}
					else if (i->type == angel_fortress || i->type == arcangel_fortress)
					{
						s.x_offset = 32 - 8 / 2;
						s.y_offset = 64;
					}

					s.untransformed_location = i->untransformed_location;
					s.start_time = std::chrono::high_resolution_clock::now();
					souls.push_front(s);

					//cout << "good guy total " << good_guy_fish_total << endl;
				}

				i++;
			}
		}

		// Get demon damage
		for (auto i = curr_level.demons.begin(); i != curr_level.demons.end();)
		{
			vertex_3 v = i->untransformed_location;
			transform(v);

			float U = 0;
			float avg_max_damage = 0;

			for (auto j = curr_level.angels.begin(); j != curr_level.angels.end(); j++)
			{
				vertex_3 l = j->untransformed_location;
				transform(l);

				vertex_3 ray = v - l;

				float distance = ray.length();

				if (distance == 0)
					distance = 0.0000001f;

				U = add_vel(U, pow(j->mass / distance, 0.5f));

				avg_max_damage += j->max_damage;
			}

			float t = sqrtf(1.0f - U * U);

			if (curr_level.angels.size() == 0)
				avg_max_damage = 0;
			else
				avg_max_damage /= curr_level.angels.size();

			float y = static_cast<float>(mt_rand()) / static_cast<float>(static_cast<long unsigned int>(-1));

			long long signed int damage = static_cast<long signed int>(round(avg_max_damage * (1.0f - t) * y));


			if (damage > 0)
			{
				ostringstream oss;
				oss << "-" << damage;

				text_snippet ts(oss.str());
				ts.untransformed_location = i->untransformed_location;
				ts.start_time = std::chrono::high_resolution_clock::now();
				ts.x_offset = 32 - static_cast<long signed int>(get_sentence_width(mimgs, oss.str()) / 2);
				ts.y_offset = -48;
				text_snippets.push_back(ts);
			}


			if (false == developer_mode)
				i->hit_points -= damage;

			if (i->hit_points <= 0)
			{
				i = curr_level.demons.erase(i);

				if (curr_level.demons.size() == 0)
				{
					if (curr_level.level_hint < (levels.size() - 1))
					{
						state = STATE_LEVEL_WIN;
						return;
					}
					else
					{
						state = STATE_GAME_END;
						return;
					}
				}
			}
			else
			{
				if (t == 0)
					t = 0.0000001f;

				// do fishing here
				long unsigned int x = static_cast<long unsigned int>(1.0f / t);

				//				cout << "demon x " << x << endl;

				if (0 == mt_rand() % x)
				{
					curr_level.bad_guy_fish_total += i->fish_rate;

					soul s;
					s.opengl_init(soul_image);

					if (i->type == demon || i->type == arcdemon)
					{
						s.x_offset = 32 - 8 / 2;
						s.y_offset = 64;
					}
					else if (i->type == demon_boat || i->type == arcdemon_boat)
					{
						s.x_offset = 32 - 8 / 2;
						s.y_offset = 64;
					}
					else if (i->type == demon_fortress || i->type == arcdemon_fortress)
					{
						s.x_offset = 32 - 8 / 2;
						s.y_offset = 64;
					}

					s.untransformed_location = i->untransformed_location;
					s.start_time = std::chrono::high_resolution_clock::now();
					souls.push_front(s);


					//cout << "bad guy total " << bad_guy_fish_total << endl;
				}

				i++;
			}
		}


	}
}

void idle_func(void)
{
	if (state == STATE_GAME)
	{
		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - level_started_at;

		if (elapsed.count()/*- pause_elapsed.count()*/ >= 2000.0f)
		{
			//if (pause_elapsed.count() > 0)
			//{
			//	ostringstream oss;
			//	oss << elapsed.count() << " " << pause_elapsed.count();

			//	SDL_ShowSimpleMessageBox(MB_OK, "title", oss.str().c_str(), gWindow);

			//	pause_elapsed = std::chrono::duration<float, std::milli>(pause_start - pause_start);
			//}

			game_idle_func();




		}

	}
}






vertex_3 get_sea_colour_from_gravitation(vertex_3 v)
{
	float U_angel = 0;

	for (list<good_guy>::const_iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
	{
		vertex_3 l = i->untransformed_location;
		transform(l);

		vertex_3 ray = v - l;

		float distance = ray.length();

		if (distance == 0)
			distance = 0.0000001f;

		U_angel = add_vel(U_angel, pow(i->mass / distance, 0.5f));
	}

	float t_angel = sqrtf(1.0f - U_angel * U_angel);

	float U_demon = 0;

	for (list<bad_guy>::const_iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
	{
		vertex_3 l = i->untransformed_location;
		transform(l);

		vertex_3 ray = v - l;

		float distance = ray.length();

		if (distance == 0)
			distance = 0.0000001f;

		U_demon = add_vel(U_demon, pow(i->mass / distance, 0.5f));
	}

	float t_demon = sqrtf(1.0f - U_demon * U_demon);

	vertex_3 colour(1.0f, 1 - t_demon, 1 - t_angel);


	vertex_3 red(1.0f, 0.0f, 0.0f);

	vertex_3 pc(player_colour[0], player_colour[1], player_colour[2]);
	vertex_3 ec(enemy_colour[0], enemy_colour[1], enemy_colour[2]);

	vertex_3 final_colour = lin_interp(red, pc, 1 - t_angel);
	final_colour = lin_interp(final_colour, ec, 1 - t_demon);
	return colour;// final_colour;


	//float gray_level = final_colour.x + final_colour.y + final_colour.z;
	//gray_level /= 3.0f;

	//vertex_3 gray_colour(gray_level, gray_level, gray_level);

	//return lin_interp(final_colour, gray_colour, 0.5f);



}

vertex_3 get_land_colour_from_gravitation(const vertex_3& v)
{
	float U_angel = 0;

	for (list<good_guy>::const_iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
	{
		vertex_3 l = i->untransformed_location;
		transform(l);

		vertex_3 ray = v - l;

		float distance = ray.length();

		if (distance == 0)
			distance = 0.0000001f;

		U_angel = add_vel(U_angel, pow(i->mass / distance, 0.5f));
	}

	float t_angel = sqrtf(1.0f - U_angel * U_angel);

	float U_demon = 0;

	for (list<bad_guy>::const_iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
	{
		vertex_3 l = i->untransformed_location;
		transform(l);

		vertex_3 ray = v - l;

		float distance = ray.length();

		if (distance == 0)
			distance = 0.0000001f;

		U_demon = add_vel(U_demon, pow(i->mass / distance, 0.5f));
	}

	float t_demon = sqrtf(1.0f - U_demon * U_demon);

	vertex_3 colour(1.0f, t_angel, t_demon);

	vertex_3 white(1.0f, 1.0f, 1.0f);

	vertex_3 pc(player_colour[0], player_colour[1], player_colour[2]);
	vertex_3 ec(enemy_colour[0], enemy_colour[1], enemy_colour[2]);

	vertex_3 final_colour = lin_interp(white, pc, 1 - t_angel);
	final_colour = lin_interp(final_colour, ec, 1 - t_demon);

	return colour;// final_colour;
}


void draw_game_objects(void)
{
	vector<triangle> land_triangles;
	vector<line_segment> line_segments;
	vector<triangle> sea_triangles;

	land_triangles = untransformed_triangles;
	line_segments = untransformed_line_segments;
	sea_triangles = untransformed_sea_triangles;


	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	perspective.use_program();

	vertex_3 x_vertex(1, 0, 0);
	vertex_3 look_at_ray = camera_pos - look_at_pos;
	look_at_ray.normalize();

	vertex_3 up = x_vertex.cross(look_at_ray);

	for (size_t i = 0; i < land_triangles.size(); i++)
	{
		transform(land_triangles[i].vertex[0]);
		transform(land_triangles[i].vertex[1]);
		transform(land_triangles[i].vertex[2]);
	}

	for (size_t i = 0; i < line_segments.size(); i++)
	{
		transform(line_segments[i].vertex[0]);
		transform(line_segments[i].vertex[1]);
	}

	for (size_t i = 0; i < sea_triangles.size(); i++)
	{
		// poor man's polygon offset
		sea_triangles[i].vertex[0].z += 0.01f;
		sea_triangles[i].vertex[1].z += 0.01f;
		sea_triangles[i].vertex[2].z += 0.01f;

		transform(sea_triangles[i].vertex[0]);
		transform(sea_triangles[i].vertex[1]);
		transform(sea_triangles[i].vertex[2]);
	}




	init_perspective_camera(45.0f,
		float(win_x) / float(win_y),
		0.01f, 10000.0f,
		camera_pos.x, camera_pos.y, camera_pos.z, // Camera position.
		look_at_pos.x, look_at_pos.y, look_at_pos.z, // Look at position.
		up.x, up.y, up.z, // Up direction vector.
		projection_modelview_mat);

	glUniformMatrix4fv(glGetUniformLocation(perspective.get_program(), "mvp_matrix"), 1, GL_FALSE, &projection_modelview_mat[0]);

	vector<float> sea_triangle_data;
	vector<float> land_triangle_data;
	vector<float> landmass_outline_data;

	map<vertex_3, vertex_3> sea_vertex_colours;
	map<vertex_3, vertex_3> land_vertex_colours;

	for (size_t i = 0; i < sea_triangles.size(); i++)
	{
		// Make sure you don't calculate each vertex more than once
		map<vertex_3, vertex_3>::const_iterator find_iter;

		find_iter = sea_vertex_colours.find(sea_triangles[i].vertex[0]);

		if (find_iter == sea_vertex_colours.end())
		{
			vertex_3 sea_colour = get_sea_colour_from_gravitation(sea_triangles[i].vertex[0]);
			sea_vertex_colours[sea_triangles[i].vertex[0]] = sea_colour;
		}

		find_iter = sea_vertex_colours.find(sea_triangles[i].vertex[1]);

		if (find_iter == sea_vertex_colours.end())
		{
			vertex_3 sea_colour = get_sea_colour_from_gravitation(sea_triangles[i].vertex[1]);
			sea_vertex_colours[sea_triangles[i].vertex[1]] = sea_colour;
		}

		find_iter = sea_vertex_colours.find(sea_triangles[i].vertex[2]);

		if (find_iter == sea_vertex_colours.end())
		{
			vertex_3 sea_colour = get_sea_colour_from_gravitation(sea_triangles[i].vertex[2]);
			sea_vertex_colours[sea_triangles[i].vertex[2]] = sea_colour;
		}
	}


	//vector<float> sea_triangle_red_data;

	for (size_t i = 0; i < sea_triangles.size(); i++)
	{
		map<vertex_3, vertex_3>::const_iterator find_iter;

		find_iter = sea_vertex_colours.find(sea_triangles[i].vertex[0]);

		sea_triangle_data.push_back(sea_triangles[i].vertex[0].x);
		sea_triangle_data.push_back(sea_triangles[i].vertex[0].y);
		sea_triangle_data.push_back(sea_triangles[i].vertex[0].z);
		sea_triangle_data.push_back(find_iter->second.x);
		sea_triangle_data.push_back(find_iter->second.y);
		sea_triangle_data.push_back(find_iter->second.z);

		find_iter = sea_vertex_colours.find(sea_triangles[i].vertex[1]);

		sea_triangle_data.push_back(sea_triangles[i].vertex[1].x);
		sea_triangle_data.push_back(sea_triangles[i].vertex[1].y);
		sea_triangle_data.push_back(sea_triangles[i].vertex[1].z);
		sea_triangle_data.push_back(find_iter->second.x);
		sea_triangle_data.push_back(find_iter->second.y);
		sea_triangle_data.push_back(find_iter->second.z);

		find_iter = sea_vertex_colours.find(sea_triangles[i].vertex[2]);

		sea_triangle_data.push_back(sea_triangles[i].vertex[2].x);
		sea_triangle_data.push_back(sea_triangles[i].vertex[2].y);
		sea_triangle_data.push_back(sea_triangles[i].vertex[2].z);
		sea_triangle_data.push_back(find_iter->second.x);
		sea_triangle_data.push_back(find_iter->second.y);
		sea_triangle_data.push_back(find_iter->second.z);













		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[0].x);
		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[0].y);
		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[0].z);
		//sea_triangle_red_data.push_back(1.0f);
		//sea_triangle_red_data.push_back(0.0f);
		//sea_triangle_red_data.push_back(0.0f);

		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[1].x);
		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[1].y);
		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[1].z);
		//sea_triangle_red_data.push_back(1.0f);
		//sea_triangle_red_data.push_back(0.0f);
		//sea_triangle_red_data.push_back(0.0f);

		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[2].x);
		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[2].y);
		//sea_triangle_red_data.push_back(sea_triangles[i].vertex[2].z);
		//sea_triangle_red_data.push_back(1.0f);
		//sea_triangle_red_data.push_back(0.0f);
		//sea_triangle_red_data.push_back(0.0f);


	}


	for (size_t i = 0; i < land_triangles.size(); i++)
	{
		vertex_3 land_colour(1.0, 1.0, 1.0);

		// Make sure you don't calculate each vertex more than once
		map<vertex_3, vertex_3>::const_iterator find_iter;

		find_iter = land_vertex_colours.find(land_triangles[i].vertex[0]);

		if (find_iter == land_vertex_colours.end())
		{
			vertex_3 land_colour = get_land_colour_from_gravitation(land_triangles[i].vertex[0]);
			land_vertex_colours[land_triangles[i].vertex[0]] = land_colour;
		}

		find_iter = land_vertex_colours.find(land_triangles[i].vertex[1]);

		if (find_iter == land_vertex_colours.end())
		{
			vertex_3 land_colour = get_land_colour_from_gravitation(land_triangles[i].vertex[1]);
			land_vertex_colours[land_triangles[i].vertex[1]] = land_colour;
		}

		find_iter = land_vertex_colours.find(land_triangles[i].vertex[2]);

		if (find_iter == land_vertex_colours.end())
		{
			vertex_3 land_colour = get_land_colour_from_gravitation(land_triangles[i].vertex[2]);
			land_vertex_colours[land_triangles[i].vertex[2]] = land_colour;
		}
	}

	for (size_t i = 0; i < land_triangles.size(); i++)
	{
		map<vertex_3, vertex_3>::const_iterator find_iter;

		find_iter = land_vertex_colours.find(land_triangles[i].vertex[0]);

		land_triangle_data.push_back(land_triangles[i].vertex[0].x);
		land_triangle_data.push_back(land_triangles[i].vertex[0].y);
		land_triangle_data.push_back(land_triangles[i].vertex[0].z);
		land_triangle_data.push_back(find_iter->second.x);
		land_triangle_data.push_back(find_iter->second.y);
		land_triangle_data.push_back(find_iter->second.z);

		find_iter = land_vertex_colours.find(land_triangles[i].vertex[1]);

		land_triangle_data.push_back(land_triangles[i].vertex[1].x);
		land_triangle_data.push_back(land_triangles[i].vertex[1].y);
		land_triangle_data.push_back(land_triangles[i].vertex[1].z);
		land_triangle_data.push_back(find_iter->second.x);
		land_triangle_data.push_back(find_iter->second.y);
		land_triangle_data.push_back(find_iter->second.z);

		find_iter = land_vertex_colours.find(land_triangles[i].vertex[2]);

		land_triangle_data.push_back(land_triangles[i].vertex[2].x);
		land_triangle_data.push_back(land_triangles[i].vertex[2].y);
		land_triangle_data.push_back(land_triangles[i].vertex[2].z);
		land_triangle_data.push_back(find_iter->second.x);
		land_triangle_data.push_back(find_iter->second.y);
		land_triangle_data.push_back(find_iter->second.z);
	}

	vertex_3 colour;

	colour.x = 0;
	colour.y = 0;
	colour.z = 0;

	for (size_t i = 0; i < line_segments.size(); i++)
	{
		landmass_outline_data.push_back(line_segments[i].vertex[0].x);
		landmass_outline_data.push_back(line_segments[i].vertex[0].y);
		landmass_outline_data.push_back(line_segments[i].vertex[0].z);
		landmass_outline_data.push_back(colour.x);
		landmass_outline_data.push_back(colour.y);
		landmass_outline_data.push_back(colour.z);

		landmass_outline_data.push_back(line_segments[i].vertex[1].x);
		landmass_outline_data.push_back(line_segments[i].vertex[1].y);
		landmass_outline_data.push_back(line_segments[i].vertex[1].z);
		landmass_outline_data.push_back(colour.x);
		landmass_outline_data.push_back(colour.y);
		landmass_outline_data.push_back(colour.z);
	}



	glDeleteBuffers(1, &buffer_handle);
	glGenBuffers(1, &buffer_handle);

	GLuint components_per_vertex = 6;
	GLuint components_per_position = 3;
	GLuint components_per_colour = 3;

	GLuint num_vertices = static_cast<GLuint>(sea_triangle_data.size()) / components_per_vertex;

	glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);

	glBufferData(GL_ARRAY_BUFFER, sea_triangle_data.size() * sizeof(GLfloat), &sea_triangle_data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "position"));
	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "position"),
		components_per_position,
		GL_FLOAT,
		GL_FALSE,
		components_per_vertex * sizeof(GLfloat),
		NULL);

	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "colour"));
	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "colour"),
		components_per_colour,
		GL_FLOAT,
		GL_TRUE,
		components_per_vertex * sizeof(GLfloat),
		(const GLvoid*)(components_per_position * sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, num_vertices);




	ortho.use_program();


	//for (list<wave>::iterator i = waves.begin(); i != waves.end(); )
	//{
	//	vertex_3 transformed_vertex = i->untransformed_location;
	//	transform(transformed_vertex);

	//	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	//	std::chrono::duration<float, std::milli> elapsed = end_time - i->start_time;

	//	if (elapsed.count() > 1000)
	//	{
	//		//i = waves.erase(i);
	//		i->start_time = std::chrono::high_resolution_clock::now();
	//		i->opengl_init(wave_image);
	//		i++;

	//		//wave w;
	//		//w.opengl_init(wave_image);
	//		//w.x_offset = 0;
	//		//w.y_offset = 0;
	//		//w.untransformed_location = i->untransformed_location;
	//		//w.start_time = std::chrono::high_resolution_clock::now();
	//		//waves.push_front(w);
	//	}
	//	else
	//	{
	//		vertex_3 p = get_screen_coords_from_world_coords(transformed_vertex, camera_pos, projection_modelview_mat, win_x, win_y);
	//		i->draw(ortho.get_program(), static_cast<size_t>(p.x), static_cast<size_t>(p.y), win_x, win_y);

	//		i++;
	//	}
	//}



	perspective.use_program();




	//
	//
	//	glDeleteBuffers(1, &buffer_handle);
	//	glGenBuffers(1, &buffer_handle);
	//
	//	components_per_vertex = 6;
	//	components_per_position = 3;
	//	components_per_colour = 3;
	//
	//	num_vertices = static_cast<GLuint>(sea_triangle_red_data.size()) / components_per_vertex;
	//
	//	glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
	//
	//	glBufferData(GL_ARRAY_BUFFER, sea_triangle_red_data.size() * sizeof(GLfloat), &sea_triangle_red_data[0], GL_STATIC_DRAW);
	//
	//	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "position"));
	//	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "position"),
	//		components_per_position,
	//		GL_FLOAT,
	//		GL_FALSE,
	//		components_per_vertex * sizeof(GLfloat),
	//		NULL);
	//
	//	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "colour"));
	//	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "colour"),
	//		components_per_colour,
	//		GL_FLOAT,
	//		GL_TRUE,
	//		components_per_vertex * sizeof(GLfloat),
	//		(const GLvoid*)(components_per_position * sizeof(GLfloat)));
	//
	//
	//
	//	glEnable(GL_POLYGON_STIPPLE);
	//
	//	GLubyte halftone[] = {
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
	//
	//	glPolygonStipple(halftone);
	//
	//
	//	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	//	glDisable(GL_POLYGON_STIPPLE);


	glDisable(GL_DEPTH_TEST);

	glDeleteBuffers(1, &buffer_handle);
	glGenBuffers(1, &buffer_handle);

	components_per_vertex = 6;
	components_per_position = 3;
	components_per_colour = 3;

	num_vertices = static_cast<GLuint>(land_triangle_data.size()) / components_per_vertex;

	glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);

	glBufferData(GL_ARRAY_BUFFER, land_triangle_data.size() * sizeof(GLfloat), &land_triangle_data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "position"));
	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "position"),
		components_per_position,
		GL_FLOAT,
		GL_FALSE,
		components_per_vertex * sizeof(GLfloat),
		NULL);

	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "colour"));
	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "colour"),
		components_per_colour,
		GL_FLOAT,
		GL_TRUE,
		components_per_vertex * sizeof(GLfloat),
		(const GLvoid*)(components_per_position * sizeof(GLfloat)));





	glDrawArrays(GL_TRIANGLES, 0, num_vertices);








	glDisable(GL_DEPTH_TEST);

	glLineWidth(3.0);

	glDeleteBuffers(1, &buffer_handle);
	glGenBuffers(1, &buffer_handle);

	components_per_vertex = 6;
	components_per_position = 3;
	components_per_colour = 3;

	num_vertices = static_cast<GLuint>(landmass_outline_data.size()) / components_per_vertex;

	glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);

	glBufferData(GL_ARRAY_BUFFER, landmass_outline_data.size() * sizeof(GLfloat), &landmass_outline_data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "position"));
	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "position"),
		components_per_position,
		GL_FLOAT,
		GL_FALSE,
		components_per_vertex * sizeof(GLfloat),
		NULL);

	glEnableVertexAttribArray(glGetAttribLocation(perspective.get_program(), "colour"));
	glVertexAttribPointer(glGetAttribLocation(perspective.get_program(), "colour"),
		components_per_colour,
		GL_FLOAT,
		GL_TRUE,
		components_per_vertex * sizeof(GLfloat),
		(const GLvoid*)(components_per_position * sizeof(GLfloat)));

	glDrawArrays(GL_LINES, 0, num_vertices);

	glEnable(GL_DEPTH_TEST);


	ortho.use_program();


	for (list<soul>::iterator i = souls.begin(); i != souls.end(); )
	{
		vertex_3 transformed_vertex = i->untransformed_location;
		transform(transformed_vertex);

		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - i->start_time;

		if (elapsed.count() > 500)
			i = souls.erase(i);
		else
		{
			vertex_3 p = get_screen_coords_from_world_coords(transformed_vertex, camera_pos, projection_modelview_mat, win_x, win_y);
			i->draw(ortho.get_program(), static_cast<size_t>(p.x), static_cast<size_t>(p.y), win_x, win_y);

			i++;
		}
	}







	for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
	{
		vertex_3 transformed_vertex = i->untransformed_location;
		transform(transformed_vertex);

		vertex_3 p = get_screen_coords_from_world_coords(transformed_vertex, camera_pos, projection_modelview_mat, win_x, win_y);
		i->draw(ortho.get_program(), static_cast<size_t>(p.x), static_cast<size_t>(p.y), win_x, win_y);
	}


	for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
	{
		vertex_3 transformed_vertex = i->untransformed_location;
		transform(transformed_vertex);

		vertex_3 p = get_screen_coords_from_world_coords(transformed_vertex, camera_pos, projection_modelview_mat, win_x, win_y);
		i->draw(ortho.get_program(), static_cast<size_t>(p.x), static_cast<size_t>(p.y), win_x, win_y);
	}



	RGB_uchar text_colour;

	text_colour.r = 255;
	text_colour.g = 255;
	text_colour.b = 255;

	for (size_t i = 0; i < mimgs.size(); i++)
		mimgs[i].opengl_init(text_colour);


	long long signed int spacer = win_x / 2 - tb.width / 2;

	if (spacer < 0)
		spacer = 0;

	size_t s = spacer;

	vector<string> names = { "Angel",
	"Arcangel",
	"Angel Boat",
	"Arcangel Boat",
	"Angel Fortress",
	"Arcangel Fortress" };

	vector<long long unsigned int> prices = { angel_cost,
		arcangel_cost,
		angel_boat_cost,
		arcangel_boat_cost,
		angel_fortress_cost,
		arcangel_fortress_cost };

	vector<long long unsigned int> hp = { angel_max_hit_points,
	arcangel_max_hit_points,
	angel_boat_max_hit_points,
	arcangel_boat_max_hit_points,
	angel_fortress_max_hit_points,
	arcangel_fortress_max_hit_points };


	vector<float> mass = { angel_max_mass,
	arcangel_max_mass,
	angel_boat_max_mass,
	arcangel_boat_max_mass,
	angel_fortress_max_mass,
	arcangel_fortress_max_mass };

	vector<long long unsigned int> fish_rates = { angel_fish_rate,
	arcangel_fish_rate,
	angel_boat_fish_rate,
	arcangel_boat_fish_rate,
	angel_fortress_fish_rate,
	arcangel_fortress_fish_rate };

	vector<long long unsigned int> max_damages = { angel_max_damage,
	arcangel_max_damage,
	angel_boat_max_damage,
	arcangel_boat_max_damage,
	angel_fortress_max_damage,
	arcangel_fortress_max_damage };

	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	tb.draw(ortho_colour.get_program(), ortho.get_program(),
		s,
		0, 0,
		mouse_x, mouse_y,
		win_x, win_y,
		names,
		prices,
		hp,
		mass,
		fish_rates,
		max_damages,
		curr_level.good_guy_fish_total,
		g_type + 1,
		mimgs);

	ortho.use_program();

	text_colour.r = 255;
	text_colour.g = 255;
	text_colour.b = 255;

	for (size_t i = 0; i < mimgs.size(); i++)
		mimgs[i].opengl_init(text_colour);

		
	log_system.clear();
	log_system.set_max_size(2);
	ostringstream oss;
	oss << "Souls: ";
	log_system.add_string_to_contents(oss.str());
	oss.clear();
	oss.str("");
	oss << curr_level.good_guy_fish_total;
	log_system.add_string_to_contents(oss.str());

	size_t tile_x_pos = spacer + 8 * 64 + 30;
	size_t tile_y_pos = 30;

	for (size_t i = 0; i < log_system.get_contents_size(); i++)
	{
		string s;
		log_system.get_string_from_contents(i, s);
		print_sentence(mimgs, ortho.get_program(), win_x, win_y, tile_x_pos, tile_y_pos, s);
		tile_y_pos += 20;
	}

	if (developer_mode)
	{
		RGB_uchar text_colour;

		text_colour.r = 0;
		text_colour.g = 0;
		text_colour.b = 0;

		for (size_t i = 0; i < mimgs.size(); i++)
			mimgs[i].opengl_init(text_colour);

		log_system.clear();
		log_system.set_max_size(100);

		oss.clear();
		oss.str("");
		oss << "Demon soul count: " << curr_level.bad_guy_fish_total;
		log_system.add_string_to_contents(oss.str());

		log_system.add_string_to_contents("-------------------------------------------------");

		log_system.add_string_to_contents("z - zero out angel souls");
		log_system.add_string_to_contents("x - give souls to angels");
		log_system.add_string_to_contents("c - zero out demon souls");
		log_system.add_string_to_contents("v - give souls to demons");

		log_system.add_string_to_contents("n - previous level");
		log_system.add_string_to_contents("m - next level");

		log_system.add_string_to_contents("s - save to disk");
		log_system.add_string_to_contents("p - new level");

		log_system.add_string_to_contents("k - top up angel hit points");
		log_system.add_string_to_contents("l - top up demon hit points");

		log_system.add_string_to_contents("y - pepper with angels");
		log_system.add_string_to_contents("u - pepper with demons");




		oss.clear();
		oss.str("");
		oss << "w - switch between good and bad, currently ";

		if (good_guy_mode)
			oss << " good guy mode";
		else
			oss << " bad guy mode";

		log_system.add_string_to_contents(oss.str());

		log_system.add_string_to_contents("0 - deselect piece");
		log_system.add_string_to_contents("1 - select angel/demon piece");
		log_system.add_string_to_contents("2 - select arcangel/arcdemon piece");
		log_system.add_string_to_contents("3 - select angel/demon boat piece");
		log_system.add_string_to_contents("4 - select arcangel/arcdemon boat piece");
		log_system.add_string_to_contents("5 - select angel/demon fortress piece");
		log_system.add_string_to_contents("6 - select arcangel/arcdemon fortress piece");


		tile_x_pos = 30;
		tile_y_pos = 60;

		for (size_t i = 0; i < log_system.get_contents_size(); i++)
		{
			string s;
			log_system.get_string_from_contents(i, s);
			print_sentence(mimgs, ortho.get_program(), win_x, win_y, tile_x_pos, tile_y_pos, s);
			tile_y_pos += 20;
		}
	}



	text_colour.r = 0;
	text_colour.g = 0;
	text_colour.b = 0;

	for (size_t i = 0; i < mimgs.size(); i++)
		mimgs[i].opengl_init(text_colour);

	for (list<text_snippet>::iterator i = text_snippets.begin(); i != text_snippets.end(); )
	{
		vertex_3 transformed_vertex = i->untransformed_location;
		transform(transformed_vertex);

		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - i->start_time;

		if (elapsed.count() > 500)
			i = text_snippets.erase(i);
		else
		{
			vertex_3 p = get_screen_coords_from_world_coords(transformed_vertex, camera_pos, projection_modelview_mat, win_x, win_y);
			i->draw(ortho.get_program(), static_cast<size_t>(p.x), static_cast<size_t>(p.y), win_x, win_y);

			i++;
		}
	}

}











void display_func(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (state == STATE_GAME_END)
	{
		ortho_colour.use_program();

		GLuint vbo_handle = 0, tex_handle = 0;

		glGenBuffers(1, &vbo_handle);

		complex<float> v0w;
		complex<float> v1w;
		complex<float> v2w;
		complex<float> v3w;

		complex<float> v0ndc;
		complex<float> v1ndc;
		complex<float> v2ndc;
		complex<float> v3ndc;

		v0w = complex<float>(static_cast<float>(0), static_cast<float>(0));
		v1w = complex<float>(static_cast<float>(0), static_cast<float>(win_y));
		v2w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(win_y));
		v3w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(0));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vector<GLfloat> fullscreen_vertex_data = {

			// 3D position, 4D colour coordinate
			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f // vertex 2

		};

		GLuint components_per_vertex = 7;
		GLuint components_per_position = 3;
		GLuint components_per_colour = 4;
		GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
			components_per_colour,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);







		ortho.use_program();

		glGenTextures(1, &tex_handle);

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(game_end_image.width), static_cast<GLsizei>(game_end_image.height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &game_end_image.Pixels[0]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		v0w = complex<float>(static_cast<float>(win_x / 2 - game_end_image.width / 2), static_cast<float>(win_y / 2 - game_end_image.height / 2));
		v1w = complex<float>(static_cast<float>(win_x / 2 - game_end_image.width / 2), static_cast<float>(win_y / 2 - game_end_image.height / 2 + game_end_image.height));
		v2w = complex<float>(static_cast<float>(win_x / 2 - game_end_image.width / 2 + game_end_image.width), static_cast<float>(win_y / 2 - game_end_image.height / 2 + game_end_image.height));
		v3w = complex<float>(static_cast<float>(win_x / 2 - game_end_image.width / 2 + game_end_image.width), static_cast<float>(win_y / 2 - game_end_image.height / 2));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		vector<GLfloat> logo_vertex_data = {

			// 3D position, 2D texture coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1, 0, // vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0, 0, // vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1, 1, // vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1, 0 // vertex 2
		};

		components_per_vertex = 5;
		components_per_position = 3;
		GLuint components_per_tex_coord = 2;
		num_vertices = static_cast<GLuint>(logo_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, logo_vertex_data.size() * sizeof(GLfloat), &logo_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "texcoord"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "texcoord"),
			components_per_tex_coord,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glUniform1i(glGetUniformLocation(ortho.get_program(), "tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		glDeleteTextures(1, &tex_handle);
		glDeleteBuffers(1, &vbo_handle);

		string s = "You beat the game! Click anywhere!";

		size_t sentence_width = get_sentence_width(mimgs, s);
		size_t window_width = win_x;
		size_t window_height = win_y;

		RGB_uchar text_colour;

		text_colour.r = 0;
		text_colour.g = 0;
		text_colour.b = 0;

		for (size_t i = 0; i < mimgs.size(); i++)
			mimgs[i].opengl_init(text_colour);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + level_win_image.height / 2 + 30, s);
	}
	else if (state == STATE_LEVEL_LOSE)
	{
		ortho_colour.use_program();

		GLuint vbo_handle = 0, tex_handle = 0;

		glGenBuffers(1, &vbo_handle);

		complex<float> v0w;
		complex<float> v1w;
		complex<float> v2w;
		complex<float> v3w;

		complex<float> v0ndc;
		complex<float> v1ndc;
		complex<float> v2ndc;
		complex<float> v3ndc;

		v0w = complex<float>(static_cast<float>(0), static_cast<float>(0));
		v1w = complex<float>(static_cast<float>(0), static_cast<float>(win_y));
		v2w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(win_y));
		v3w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(0));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vector<GLfloat> fullscreen_vertex_data = {

			// 3D position, 4D colour coordinate
			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f // vertex 2

		};

		GLuint components_per_vertex = 7;
		GLuint components_per_position = 3;
		GLuint components_per_colour = 4;
		GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
			components_per_colour,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);







		ortho.use_program();

		glGenTextures(1, &tex_handle);

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(level_lose_image.width), static_cast<GLsizei>(level_lose_image.height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &level_lose_image.Pixels[0]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		v0w = complex<float>(static_cast<float>(win_x / 2 - level_lose_image.width / 2), static_cast<float>(win_y / 2 - level_lose_image.height / 2));
		v1w = complex<float>(static_cast<float>(win_x / 2 - level_lose_image.width / 2), static_cast<float>(win_y / 2 - level_lose_image.height / 2 + level_lose_image.height));
		v2w = complex<float>(static_cast<float>(win_x / 2 - level_lose_image.width / 2 + level_lose_image.width), static_cast<float>(win_y / 2 - level_lose_image.height / 2 + level_lose_image.height));
		v3w = complex<float>(static_cast<float>(win_x / 2 - level_lose_image.width / 2 + level_lose_image.width), static_cast<float>(win_y / 2 - level_lose_image.height / 2));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		vector<GLfloat> logo_vertex_data = {

			// 3D position, 2D texture coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1, 0, // vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0, 0, // vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1, 1, // vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1, 0 // vertex 2
		};

		components_per_vertex = 5;
		components_per_position = 3;
		GLuint components_per_tex_coord = 2;
		num_vertices = static_cast<GLuint>(logo_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, logo_vertex_data.size() * sizeof(GLfloat), &logo_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "texcoord"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "texcoord"),
			components_per_tex_coord,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glUniform1i(glGetUniformLocation(ortho.get_program(), "tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		glDeleteTextures(1, &tex_handle);
		glDeleteBuffers(1, &vbo_handle);

		string s = "You lose! Click anywhere!";

		size_t sentence_width = get_sentence_width(mimgs, s);
		size_t window_width = win_x;
		size_t window_height = win_y;

		RGB_uchar text_colour;

		text_colour.r = 0;
		text_colour.g = 0;
		text_colour.b = 0;

		for (size_t i = 0; i < mimgs.size(); i++)
			mimgs[i].opengl_init(text_colour);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + level_win_image.height / 2 + 30, s);
	}
	else if (state == STATE_LEVEL_WIN)
	{
		ortho_colour.use_program();

		GLuint vbo_handle = 0, tex_handle = 0;

		glGenBuffers(1, &vbo_handle);

		complex<float> v0w;
		complex<float> v1w;
		complex<float> v2w;
		complex<float> v3w;

		complex<float> v0ndc;
		complex<float> v1ndc;
		complex<float> v2ndc;
		complex<float> v3ndc;

		v0w = complex<float>(static_cast<float>(0), static_cast<float>(0));
		v1w = complex<float>(static_cast<float>(0), static_cast<float>(win_y));
		v2w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(win_y));
		v3w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(0));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vector<GLfloat> fullscreen_vertex_data = {

			// 3D position, 4D colour coordinate
			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f // vertex 2

		};

		GLuint components_per_vertex = 7;
		GLuint components_per_position = 3;
		GLuint components_per_colour = 4;
		GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
			components_per_colour,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);







		ortho.use_program();

		glGenTextures(1, &tex_handle);

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(level_win_image.width), static_cast<GLsizei>(level_win_image.height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &level_win_image.Pixels[0]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		v0w = complex<float>(static_cast<float>(win_x / 2 - level_win_image.width / 2), static_cast<float>(win_y / 2 - level_win_image.height / 2));
		v1w = complex<float>(static_cast<float>(win_x / 2 - level_win_image.width / 2), static_cast<float>(win_y / 2 - level_win_image.height / 2 + level_win_image.height));
		v2w = complex<float>(static_cast<float>(win_x / 2 - level_win_image.width / 2 + level_win_image.width), static_cast<float>(win_y / 2 - level_win_image.height / 2 + level_win_image.height));
		v3w = complex<float>(static_cast<float>(win_x / 2 - level_win_image.width / 2 + level_win_image.width), static_cast<float>(win_y / 2 - level_win_image.height / 2));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		vector<GLfloat> logo_vertex_data = {

			// 3D position, 2D texture coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1, 0, // vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0, 0, // vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1, 1, // vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1, 0 // vertex 2
		};

		components_per_vertex = 5;
		components_per_position = 3;
		GLuint components_per_tex_coord = 2;
		num_vertices = static_cast<GLuint>(logo_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, logo_vertex_data.size() * sizeof(GLfloat), &logo_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "texcoord"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "texcoord"),
			components_per_tex_coord,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glUniform1i(glGetUniformLocation(ortho.get_program(), "tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		glDeleteTextures(1, &tex_handle);
		glDeleteBuffers(1, &vbo_handle);

		string s = "You win! Click anywhere!";

		size_t sentence_width = get_sentence_width(mimgs, s);
		size_t window_width = win_x;
		size_t window_height = win_y;

		RGB_uchar text_colour;

		text_colour.r = 0;
		text_colour.g = 0;
		text_colour.b = 0;

		for (size_t i = 0; i < mimgs.size(); i++)
			mimgs[i].opengl_init(text_colour);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + level_win_image.height / 2 + 30, s);
	}
	else if (state == STATE_LITTLE_RED_SPLASH_SCREEN)
	{
		ortho_colour.use_program();

		GLuint vbo_handle = 0, tex_handle = 0;

		glGenBuffers(1, &vbo_handle);

		complex<float> v0w;
		complex<float> v1w;
		complex<float> v2w;
		complex<float> v3w;

		complex<float> v0ndc;
		complex<float> v1ndc;
		complex<float> v2ndc;
		complex<float> v3ndc;

		v0w = complex<float>(static_cast<float>(0), static_cast<float>(0));
		v1w = complex<float>(static_cast<float>(0), static_cast<float>(win_y));
		v2w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(win_y));
		v3w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(0));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vector<GLfloat> fullscreen_vertex_data = {

			// 3D position, 4D colour coordinate
			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f,// vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1.0f, 1.0f, 1.0f, 1.0f // vertex 2

		};

		GLuint components_per_vertex = 7;
		GLuint components_per_position = 3;
		GLuint components_per_colour = 4;
		GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
			components_per_colour,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);







		ortho.use_program();

		glGenTextures(1, &tex_handle);

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(splash_screen_image.width), static_cast<GLsizei>(splash_screen_image.height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &splash_screen_image.Pixels[0]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		v0w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2), static_cast<float>(win_y / 2 - splash_screen_image.height / 2));
		v1w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2), static_cast<float>(win_y / 2 - splash_screen_image.height / 2 + splash_screen_image.height));
		v2w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2 + splash_screen_image.width), static_cast<float>(win_y / 2 - splash_screen_image.height / 2 + splash_screen_image.height));
		v3w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2 + splash_screen_image.width), static_cast<float>(win_y / 2 - splash_screen_image.height / 2));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		vector<GLfloat> logo_vertex_data = {

			// 3D position, 2D texture coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1, 0, // vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0, 0, // vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1, 1, // vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1, 0 // vertex 2
		};

		components_per_vertex = 5;
		components_per_position = 3;
		GLuint components_per_tex_coord = 2;
		num_vertices = static_cast<GLuint>(logo_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, logo_vertex_data.size() * sizeof(GLfloat), &logo_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "texcoord"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "texcoord"),
			components_per_tex_coord,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glUniform1i(glGetUniformLocation(ortho.get_program(), "tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		glDeleteTextures(1, &tex_handle);
		glDeleteBuffers(1, &vbo_handle);

		string s = "Click anywhere!";

		size_t sentence_width = get_sentence_width(mimgs, s);
		size_t window_width = win_x;
		size_t window_height = win_y;

		RGB_uchar text_colour;

		text_colour.r = 0;
		text_colour.g = 0;
		text_colour.b = 0;

		for (size_t i = 0; i < mimgs.size(); i++)
			mimgs[i].opengl_init(text_colour);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + splash_screen_image.height / 2 + 30, s);
	}
	else if (state == STATE_TITLE_SCREEN)
	{
		ortho_colour.use_program();

		GLuint vbo_handle = 0, tex_handle = 0;

		glGenBuffers(1, &vbo_handle);

		complex<float> v0w;
		complex<float> v1w;
		complex<float> v2w;
		complex<float> v3w;

		complex<float> v0ndc;
		complex<float> v1ndc;
		complex<float> v2ndc;
		complex<float> v3ndc;

		v0w = complex<float>(static_cast<float>(0), static_cast<float>(0));
		v1w = complex<float>(static_cast<float>(0), static_cast<float>(win_y));
		v2w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(win_y));
		v3w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(0));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vector<GLfloat> fullscreen_vertex_data = {

			// 3D position, 4D colour coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f // vertex 2

		};

		GLuint components_per_vertex = 7;
		GLuint components_per_position = 3;
		GLuint components_per_colour = 4;
		GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
			components_per_colour,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);







		ortho.use_program();

		glGenTextures(1, &tex_handle);

		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(title_screen_image.width), static_cast<GLsizei>(title_screen_image.height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &title_screen_image.Pixels[0]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		v0w = complex<float>(static_cast<float>(win_x / 2 - title_screen_image.width / 2), static_cast<float>(win_y / 2 - title_screen_image.height / 2));
		v1w = complex<float>(static_cast<float>(win_x / 2 - title_screen_image.width / 2), static_cast<float>(win_y / 2 - title_screen_image.height / 2 + title_screen_image.height));
		v2w = complex<float>(static_cast<float>(win_x / 2 - title_screen_image.width / 2 + title_screen_image.width), static_cast<float>(win_y / 2 - title_screen_image.height / 2 + title_screen_image.height));
		v3w = complex<float>(static_cast<float>(win_x / 2 - title_screen_image.width / 2 + title_screen_image.width), static_cast<float>(win_y / 2 - title_screen_image.height / 2));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		vector<GLfloat> logo_vertex_data = {

			// 3D position, 2D texture coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   1, 0, // vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0, 0, // vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   1, 1, // vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   1, 0 // vertex 2
		};

		components_per_vertex = 5;
		components_per_position = 3;
		GLuint components_per_tex_coord = 2;
		num_vertices = static_cast<GLuint>(logo_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, logo_vertex_data.size() * sizeof(GLfloat), &logo_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "texcoord"));
		glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "texcoord"),
			components_per_tex_coord,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glUniform1i(glGetUniformLocation(ortho.get_program(), "tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		glDeleteTextures(1, &tex_handle);
		glDeleteBuffers(1, &vbo_handle);

		RGB_uchar text_colour;

		text_colour.r = 255;
		text_colour.g = 255;
		text_colour.b = 255;

		for (size_t i = 0; i < mimgs.size(); i++)
			mimgs[i].opengl_init(text_colour);

		string s = "Click anywhere to begin!";

		size_t sentence_width = get_sentence_width(mimgs, s);
		size_t window_width = win_x;
		size_t window_height = win_y;

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + title_screen_image.height / 2 + 30, s);

		s = "Click on the red river in the game to fish for souls!";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + title_screen_image.height / 2 + 50, s);

		s = "Place troops and fortresses on land! Place boats on the river!";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + title_screen_image.height / 2 + 70, s);

		s = "Crush your enemy! Time is of the essence!";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + title_screen_image.height / 2 + 90, s);

		s = "Copyright ©   2020 Little Red Studio";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2 + title_screen_image.height / 2 + 110, s);
	}
	else if (state == STATE_GAME)
	{
		draw_game_objects();

		ortho_colour.use_program();

		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> elapsed = end_time - level_started_at;

		// Draw banners
		if (true == developer_mode && elapsed.count() < 2000)
		{
			size_t level = 0;

			ostringstream oss;

			oss << "Developer mode";

			string s = oss.str();

			size_t sentence_width = get_sentence_width(mimgs, s);
			size_t window_width = win_x;
			size_t window_height = win_y;

			GLuint vbo_handle = 0;

			glGenBuffers(1, &vbo_handle);

			complex<float> v0w;
			complex<float> v1w;
			complex<float> v2w;
			complex<float> v3w;

			complex<float> v0ndc;
			complex<float> v1ndc;
			complex<float> v2ndc;
			complex<float> v3ndc;

			float alpha = 1.0f - (elapsed.count() / 2000.0f);

			alpha = pow(alpha, 1.0f / 5.0f);

			v0w = complex<float>(static_cast<float>(0), static_cast<float>(window_height / 2 - 20));
			v1w = complex<float>(static_cast<float>(0), static_cast<float>(window_height / 2 + 36));
			v2w = complex<float>(static_cast<float>(win_x), static_cast<float>(window_height / 2 + 36));
			v3w = complex<float>(static_cast<float>(win_x), static_cast<float>(window_height / 2 - 20));

			v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
			v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
			v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
			v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			vector<GLfloat> fullscreen_vertex_data = {

				// 3D position, 4D colour coordinate
				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha, // vertex 0
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 2
				v1ndc.real(), v1ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 1

				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 0
				v3ndc.real(), v3ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 3
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha // vertex 2

			};

			GLuint components_per_vertex = 7;
			GLuint components_per_position = 3;
			GLuint components_per_colour = 4;
			GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

			glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

			glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
				components_per_position,
				GL_FLOAT,
				GL_FALSE,
				components_per_vertex * sizeof(GLfloat),
				NULL);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
				components_per_colour,
				GL_FLOAT,
				GL_TRUE,
				components_per_vertex * sizeof(GLfloat),
				(const GLvoid*)(components_per_position * sizeof(GLfloat)));

			glDrawArrays(GL_TRIANGLES, 0, num_vertices);

			glLineWidth(4.0f);

			vector<float> lines;
			lines.push_back(v0ndc.real());
			lines.push_back(v0ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			lines.push_back(v1ndc.real());
			lines.push_back(v1ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			lines.push_back(v2ndc.real());
			lines.push_back(v2ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			lines.push_back(v3ndc.real());
			lines.push_back(v3ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			components_per_vertex = 7;
			components_per_position = 3;
			components_per_colour = 4;

			num_vertices = static_cast<GLuint>(lines.size()) / components_per_vertex;

			glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

			glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(GLfloat), &lines[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
				components_per_position,
				GL_FLOAT,
				GL_FALSE,
				components_per_vertex * sizeof(GLfloat),
				NULL);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
				components_per_colour,
				GL_FLOAT,
				GL_TRUE,
				components_per_vertex * sizeof(GLfloat),
				(const GLvoid*)(components_per_position * sizeof(GLfloat)));

			glDrawArrays(GL_LINE_LOOP, 0, num_vertices);

			glDeleteBuffers(1, &vbo_handle);

			ortho.use_program();

			RGB_uchar text_colour;

			text_colour.r = 255;
			text_colour.g = 255;
			text_colour.b = 255;

			for (size_t i = 0; i < mimgs.size(); i++)
				mimgs[i].opengl_init(text_colour, alpha * 255.0f);

			print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2, s);

		}
		else if (false == developer_mode && elapsed.count() < 2000)
		{
			ostringstream oss;

			oss << "Level " << (curr_level.level_hint + 1);

			string s = oss.str();

			size_t sentence_width = get_sentence_width(mimgs, s);
			size_t window_width = win_x;
			size_t window_height = win_y;

			GLuint vbo_handle = 0;

			glGenBuffers(1, &vbo_handle);

			complex<float> v0w;
			complex<float> v1w;
			complex<float> v2w;
			complex<float> v3w;

			complex<float> v0ndc;
			complex<float> v1ndc;
			complex<float> v2ndc;
			complex<float> v3ndc;

			float alpha = 1.0f - (elapsed.count() / 2000.0f);

			alpha = pow(alpha, 1.0f / 5.0f);

			v0w = complex<float>(static_cast<float>(0), static_cast<float>(window_height / 2 - 20));
			v1w = complex<float>(static_cast<float>(0), static_cast<float>(window_height / 2 + 36));
			v2w = complex<float>(static_cast<float>(win_x), static_cast<float>(window_height / 2 + 36));
			v3w = complex<float>(static_cast<float>(win_x), static_cast<float>(window_height / 2 - 20));

			v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
			v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
			v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
			v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			vector<GLfloat> fullscreen_vertex_data = {

				// 3D position, 4D colour coordinate
				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha, // vertex 0
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 2
				v1ndc.real(), v1ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 1

				v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 0
				v3ndc.real(), v3ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha,// vertex 3
				v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, alpha // vertex 2

			};

			GLuint components_per_vertex = 7;
			GLuint components_per_position = 3;
			GLuint components_per_colour = 4;
			GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

			glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

			glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
				components_per_position,
				GL_FLOAT,
				GL_FALSE,
				components_per_vertex * sizeof(GLfloat),
				NULL);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
				components_per_colour,
				GL_FLOAT,
				GL_TRUE,
				components_per_vertex * sizeof(GLfloat),
				(const GLvoid*)(components_per_position * sizeof(GLfloat)));

			glDrawArrays(GL_TRIANGLES, 0, num_vertices);

			glLineWidth(4.0f);

			vector<float> lines;
			lines.push_back(v0ndc.real());
			lines.push_back(v0ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			lines.push_back(v1ndc.real());
			lines.push_back(v1ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			lines.push_back(v2ndc.real());
			lines.push_back(v2ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			lines.push_back(v3ndc.real());
			lines.push_back(v3ndc.imag());
			lines.push_back(0);
			lines.push_back(1);
			lines.push_back(0);
			lines.push_back(0);
			lines.push_back(alpha);

			components_per_vertex = 7;
			components_per_position = 3;
			components_per_colour = 4;

			num_vertices = static_cast<GLuint>(lines.size()) / components_per_vertex;

			glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

			glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(GLfloat), &lines[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
				components_per_position,
				GL_FLOAT,
				GL_FALSE,
				components_per_vertex * sizeof(GLfloat),
				NULL);

			glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
			glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
				components_per_colour,
				GL_FLOAT,
				GL_TRUE,
				components_per_vertex * sizeof(GLfloat),
				(const GLvoid*)(components_per_position * sizeof(GLfloat)));



			glDrawArrays(GL_LINE_LOOP, 0, num_vertices);



			glDeleteBuffers(1, &vbo_handle);

			ortho.use_program();

			RGB_uchar text_colour;

			text_colour.r = 255;
			text_colour.g = 255;
			text_colour.b = 255;

			for (size_t i = 0; i < mimgs.size(); i++)
				mimgs[i].opengl_init(text_colour, alpha * 255.0f);

			print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 2, s);
		}






		//perspective.use_program();

		//glPointSize(4.0);

		//glBegin(GL_POINTS);

		//for (size_t i = 0; i < ortho_collision_island_points.size(); i++)
		//{
		//	vertex_3 v = ortho_collision_island_points[i];
		//	transform(v);

		//	glColor3f(1, 1, 1);

		//	glVertex3f(v.x, v.y, v.z);

		//}

		//for (size_t i = 0; i < ortho_collision_sea_points.size(); i++)
		//{
		//	vertex_3 v = ortho_collision_sea_points[i];
		//	transform(v);

		//	glVertex3f(v.x, v.y, v.z);
		//}
	}
	else if (state == STATE_PAUSE_SCREEN)
	{



		ortho_colour.use_program();

		GLuint vbo_handle = 0, tex_handle = 0;

		glGenBuffers(1, &vbo_handle);

		complex<float> v0w;
		complex<float> v1w;
		complex<float> v2w;
		complex<float> v3w;

		complex<float> v0ndc;
		complex<float> v1ndc;
		complex<float> v2ndc;
		complex<float> v3ndc;

		v0w = complex<float>(static_cast<float>(0), static_cast<float>(0));
		v1w = complex<float>(static_cast<float>(0), static_cast<float>(win_y));
		v2w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(win_y));
		v3w = complex<float>(static_cast<float>(0 + win_x), static_cast<float>(0));

		v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		vector<GLfloat> fullscreen_vertex_data = {

			// 3D position, 4D colour coordinate
			v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f, // vertex 0
			v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 2
			v1ndc.real(), v1ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 1

			v0ndc.real(), v0ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 0
			v3ndc.real(), v3ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f,// vertex 3
			v2ndc.real(), v2ndc.imag(), 0,   0.0f, 0.0f, 0.0f, 1.0f // vertex 2

		};

		GLuint components_per_vertex = 7;
		GLuint components_per_position = 3;
		GLuint components_per_colour = 4;
		GLuint num_vertices = static_cast<GLuint>(fullscreen_vertex_data.size()) / components_per_vertex;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		glBufferData(GL_ARRAY_BUFFER, fullscreen_vertex_data.size() * sizeof(GLfloat), &fullscreen_vertex_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "position"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "position"),
			components_per_position,
			GL_FLOAT,
			GL_FALSE,
			components_per_vertex * sizeof(GLfloat),
			NULL);

		glEnableVertexAttribArray(glGetAttribLocation(ortho_colour.get_program(), "colour"));
		glVertexAttribPointer(glGetAttribLocation(ortho_colour.get_program(), "colour"),
			components_per_colour,
			GL_FLOAT,
			GL_TRUE,
			components_per_vertex * sizeof(GLfloat),
			(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		glDrawArrays(GL_TRIANGLES, 0, num_vertices);








		ortho.use_program();








		//glGenTextures(1, &tex_handle);

		//glBindTexture(GL_TEXTURE_2D, tex_handle);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(splash_screen_image.width), static_cast<GLsizei>(splash_screen_image.height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &splash_screen_image.Pixels[0]);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		//v0w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2), static_cast<float>(win_y / 2 - splash_screen_image.height / 2));
		//v1w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2), static_cast<float>(win_y / 2 - splash_screen_image.height / 2 + splash_screen_image.height));
		//v2w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2 + splash_screen_image.width), static_cast<float>(win_y / 2 - splash_screen_image.height / 2 + splash_screen_image.height));
		//v3w = complex<float>(static_cast<float>(win_x / 2 - splash_screen_image.width / 2 + splash_screen_image.width), static_cast<float>(win_y / 2 - splash_screen_image.height / 2));

		//v0ndc = get_ndc_coords_from_window_coords(win_x, win_y, v0w);
		//v1ndc = get_ndc_coords_from_window_coords(win_x, win_y, v1w);
		//v2ndc = get_ndc_coords_from_window_coords(win_x, win_y, v2w);
		//v3ndc = get_ndc_coords_from_window_coords(win_x, win_y, v3w);

		//vector<GLfloat> logo_vertex_data = {

		//	// 3D position, 2D texture coordinate
		//	v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
		//	v2ndc.real(), v2ndc.imag(), 0,   1, 0, // vertex 2
		//	v1ndc.real(), v1ndc.imag(), 0,   0, 0, // vertex 1

		//	v0ndc.real(), v0ndc.imag(), 0,   0, 1, // vertex 0
		//	v3ndc.real(), v3ndc.imag(), 0,   1, 1, // vertex 3
		//	v2ndc.real(), v2ndc.imag(), 0,   1, 0 // vertex 2
		//};

		//components_per_vertex = 5;
		//components_per_position = 3;
		//GLuint components_per_tex_coord = 2;
		//num_vertices = static_cast<GLuint>(logo_vertex_data.size()) / components_per_vertex;

		//glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

		//glBufferData(GL_ARRAY_BUFFER, logo_vertex_data.size() * sizeof(GLfloat), &logo_vertex_data[0], GL_STATIC_DRAW);

		//glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "position"));
		//glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "position"),
		//	components_per_position,
		//	GL_FLOAT,
		//	GL_FALSE,
		//	components_per_vertex * sizeof(GLfloat),
		//	NULL);

		//glEnableVertexAttribArray(glGetAttribLocation(ortho.get_program(), "texcoord"));
		//glVertexAttribPointer(glGetAttribLocation(ortho.get_program(), "texcoord"),
		//	components_per_tex_coord,
		//	GL_FLOAT,
		//	GL_TRUE,
		//	components_per_vertex * sizeof(GLfloat),
		//	(const GLvoid*)(components_per_position * sizeof(GLfloat)));

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, tex_handle);
		//glUniform1i(glGetUniformLocation(ortho.get_program(), "tex"), 0);

		//glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		//glDeleteTextures(1, &tex_handle);
		//glDeleteBuffers(1, &vbo_handle);


		ortho.use_program();


		RGB_uchar text_colour;

		text_colour.r = 255;
		text_colour.g = 255;
		text_colour.b = 255;

		for (size_t i = 0; i < mimgs.size(); i++)
			mimgs[i].opengl_init(text_colour);



		string s = "Paused. Press esc to continue!";

		size_t sentence_width = get_sentence_width(mimgs, s);
		size_t window_width = win_x;
		size_t window_height = win_y;

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 3, s);

		s = "Credits:";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 3 + 40, s);

		s = "Programming - Shawn Halayka";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 3 + 60, s);

		s = "Design - Sam Rotthier, Shawn Halayka, Indra Ongena";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 3 + 80, s);

		s = "Art - Anna Morozova";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 3 + 100, s);

		s = "Dear ImGui library - Omar Cornut";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 3 + 120, s);

		s = "Simple SDL2 Audio library - Jake Besworth";

		sentence_width = get_sentence_width(mimgs, s);

		print_sentence(mimgs, ortho.get_program(), win_x, win_y, window_width / 2 - sentence_width / 2, window_height / 3 + 140, s);



		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(gWindow);
		ImGui::NewFrame();

		ImGui::SetNextWindowSize(ImVec2(400, 150));
		ImGui::SetNextWindowPos(ImVec2(float(win_x / 2 - 400 / 2), 10));

		ImGui::Begin("Controls");
		ImGui::SliderInt("Volume", &global_volume, 0, SDL_MIX_MAXVOLUME);
		ImGui::SliderInt("Difficulty", &difficulty, 1, max_difficulty);

		
		ImGui::ColorEdit3("Player colour", player_colour);


		ImGui::ColorEdit3("Enemy colour", enemy_colour);

		ImGui::End();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}

void game_handle_left_mouse_click(int x, int y)
{
	ui_picked = false;
	island_picked = false;
	sea_picked = false;

	vertex_3 picked_location;

	get_collision_perspective(x, y, ui_picked, island_picked, sea_picked, picked_location);

	if (ui_picked)
	{
		// use x and y here
		long long signed int spacer = win_x / 2 - tb.width / 2;

		if (spacer < 0)
			spacer = 0;

		if (x < spacer + 64)
		{
			z_angle -= pi / 8;
			g_type = angel_none;
		}
		else if (x < spacer + 64 * 2)
		{
			z_angle += pi / 8;
			g_type = angel_none;
		}
		else if (x < spacer + 64 * 3)
		{
			g_type = angel;
		}
		else if (x < spacer + 64 * 4)
		{
			g_type = arcangel;
		}
		else if (x < spacer + 64 * 5)
		{
			g_type = angel_boat;
		}
		else if (x < spacer + 64 * 6)
		{
			g_type = arcangel_boat;
		}
		else if (x < spacer + 64 * 7)
		{
			g_type = angel_fortress;
		}
		else if (x < spacer + 64 * 8)
		{
			g_type = arcangel_fortress;
		}




	}
	else if (island_picked)
	{
		if (good_guy_mode)
		{
			if (g_type == angel && curr_level.good_guy_fish_total >= angel_cost)
			{
				good_guy a;
				a.mass = angel_max_mass;
				a.hit_points = a.max_hit_points = angel_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = angel_max_damage;
				a.type = angel;
				a.fish_rate = angel_fish_rate;

				a.opengl_init(angel_image);

				curr_level.angels.push_back(a);

				curr_level.good_guy_fish_total -= angel_cost;
			}
			else if (g_type == arcangel && curr_level.good_guy_fish_total >= arcangel_cost)
			{
				good_guy a;
				a.mass = arcangel_max_mass;
				a.hit_points = a.max_hit_points = arcangel_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = arcangel_max_damage;
				a.type = arcangel;
				a.fish_rate = arcangel_fish_rate;

				a.opengl_init(arcangel_image);

				curr_level.angels.push_back(a);

				curr_level.good_guy_fish_total -= arcangel_cost;
			}
			else if (g_type == angel_fortress && curr_level.good_guy_fish_total >= angel_fortress_cost)
			{
				good_guy a;
				a.mass = angel_fortress_max_mass;
				a.hit_points = a.max_hit_points = angel_fortress_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = angel_fortress_max_damage;
				a.type = angel_fortress;
				a.fish_rate = angel_fortress_fish_rate;

				a.opengl_init(angel_fortress_image);

				curr_level.angels.push_back(a);

				curr_level.good_guy_fish_total -= angel_fortress_cost;
			}
			else if (g_type == arcangel_fortress && curr_level.good_guy_fish_total >= arcangel_fortress_cost)
			{
				good_guy a;
				a.mass = arcangel_fortress_max_mass;
				a.hit_points = a.max_hit_points = arcangel_fortress_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = arcangel_fortress_max_damage;
				a.type = arcangel_fortress;
				a.fish_rate = arcangel_fortress_fish_rate;

				a.opengl_init(arcangel_fortress_image);

				curr_level.angels.push_back(a);

				curr_level.good_guy_fish_total -= arcangel_fortress_cost;
			}
		}
		else
		{
			if (b_type == demon && curr_level.bad_guy_fish_total >= demon_cost)
			{
				bad_guy a;
				a.mass = demon_max_mass;
				a.hit_points = a.max_hit_points = demon_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = demon_max_damage;
				a.type = demon;
				a.fish_rate = demon_fish_rate;

				a.opengl_init(demon_image);

				curr_level.demons.push_back(a);

				curr_level.bad_guy_fish_total -= demon_cost;
			}
			else if (b_type == arcdemon && curr_level.bad_guy_fish_total >= arcdemon_cost)
			{
				bad_guy a;
				a.mass = arcdemon_max_mass;
				a.hit_points = a.max_hit_points = arcdemon_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = arcdemon_max_damage;
				a.type = arcdemon;
				a.fish_rate = arcdemon_fish_rate;

				a.opengl_init(arcdemon_image);

				curr_level.demons.push_back(a);

				curr_level.bad_guy_fish_total -= arcdemon_cost;
			}
			else if (b_type == demon_fortress && curr_level.bad_guy_fish_total >= demon_fortress_cost)
			{
				bad_guy a;
				a.mass = demon_fortress_max_mass;
				a.hit_points = a.max_hit_points = demon_fortress_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = demon_fortress_max_damage;
				a.type = demon_fortress;
				a.fish_rate = demon_fortress_fish_rate;

				a.opengl_init(demon_fortress_image);

				curr_level.demons.push_back(a);

				curr_level.bad_guy_fish_total -= demon_fortress_cost;
			}
			else if (b_type == arcdemon_fortress && curr_level.bad_guy_fish_total >= arcdemon_fortress_cost)
			{
				bad_guy a;
				a.mass = arcdemon_fortress_max_mass;
				a.hit_points = a.max_hit_points = arcdemon_fortress_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = arcdemon_fortress_max_damage;
				a.type = arcdemon_fortress;
				a.fish_rate = arcdemon_fortress_fish_rate;

				a.opengl_init(arcdemon_fortress_image);

				curr_level.demons.push_back(a);

				curr_level.bad_guy_fish_total -= arcdemon_fortress_cost;
			}
		}

	}
	else if (sea_picked)
	{
		if (good_guy_mode)
		{
			if (g_type == angel_boat && curr_level.good_guy_fish_total >= angel_boat_cost)
			{
				good_guy a;
				a.mass = angel_boat_max_mass;
				a.hit_points = a.max_hit_points = angel_boat_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = angel_boat_max_damage;
				a.type = angel_boat;
				a.fish_rate = angel_boat_fish_rate;

				a.opengl_init(angel_boat_image);

				curr_level.angels.push_back(a);

				curr_level.good_guy_fish_total -= angel_boat_cost;
			}
			else if (g_type == arcangel_boat && curr_level.good_guy_fish_total >= arcangel_boat_cost)
			{
				good_guy a;
				a.mass = arcangel_boat_max_mass;
				a.hit_points = a.max_hit_points = arcangel_boat_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = arcangel_boat_max_damage;
				a.type = arcangel_boat;
				a.fish_rate = arcangel_boat_fish_rate;

				a.opengl_init(arcangel_boat_image);

				curr_level.angels.push_back(a);

				curr_level.good_guy_fish_total -= arcangel_boat_cost;
			}
			else
			{
				soul s;
				s.opengl_init(soul_image);
				s.x_offset = 0;
				s.y_offset = 0;
				s.untransformed_location = picked_location;
				s.start_time = std::chrono::high_resolution_clock::now();
				souls.push_front(s);

				curr_level.good_guy_fish_total += 1;
			}
		}
		else
		{
			if (b_type == demon_boat && curr_level.bad_guy_fish_total >= demon_boat_cost)
			{
				bad_guy a;
				a.mass = demon_boat_max_mass;
				a.hit_points = a.max_hit_points = demon_boat_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = demon_boat_max_damage;
				a.type = demon_boat;
				a.fish_rate = demon_boat_fish_rate;

				a.opengl_init(demon_boat_image);

				curr_level.demons.push_back(a);

				curr_level.bad_guy_fish_total -= demon_boat_cost;
			}
			else if (b_type == arcdemon_boat && curr_level.bad_guy_fish_total >= arcdemon_boat_cost)
			{
				bad_guy a;
				a.mass = arcdemon_boat_max_mass;
				a.hit_points = a.max_hit_points = arcdemon_boat_max_hit_points;
				a.untransformed_location = picked_location;
				a.max_damage = arcdemon_boat_max_damage;
				a.type = arcdemon_boat;
				a.fish_rate = arcdemon_boat_fish_rate;

				a.opengl_init(arcdemon_boat_image);

				curr_level.demons.push_back(a);

				curr_level.bad_guy_fish_total -= arcdemon_boat_cost;
			}
			else
			{
				soul s;
				s.opengl_init(soul_image);
				s.x_offset = 0;
				s.y_offset = 0;
				s.untransformed_location = picked_location;
				s.start_time = std::chrono::high_resolution_clock::now();
				souls.push_front(s);

				curr_level.bad_guy_fish_total += 1;
			}
		}
	}
}



bool load_from_disk(const char* const file_name, level_data& ld)
{
	ifstream in(file_name, ios_base::binary);

	if (in.fail())
		return false;

	in.read(reinterpret_cast<char*>(&ld.prng_seed), sizeof(long unsigned int));

	in.read(reinterpret_cast<char*>(&ld.level_hint), sizeof(long unsigned int));

	in.read(reinterpret_cast<char*>(&ld.good_guy_fish_total), sizeof(long long unsigned int));
	in.read(reinterpret_cast<char*>(&ld.bad_guy_fish_total), sizeof(long long unsigned int));

	size_t angel_count = 0;

	in.read(reinterpret_cast<char*>(&angel_count), sizeof(size_t));

	list<good_guy> temp_angels;

	for (size_t i = 0; i < angel_count; i++)
	{
		good_guy a;

		in.read(reinterpret_cast<char*>(&a.mass), sizeof(float));
		in.read(reinterpret_cast<char*>(&a.hit_points), sizeof(long long signed int));
		in.read(reinterpret_cast<char*>(&a.max_hit_points), sizeof(long long unsigned int));
		in.read(reinterpret_cast<char*>(&a.max_damage), sizeof(long long unsigned int));
		in.read(reinterpret_cast<char*>(&a.fish_rate), sizeof(long long unsigned int));
		in.read(reinterpret_cast<char*>(&a.untransformed_location.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&a.untransformed_location.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&a.untransformed_location.z), sizeof(float));
		in.read(reinterpret_cast<char*>(&a.type), sizeof(good_type));

		if (a.type == angel)
		{
			a.opengl_init(angel_image);
		}
		else if (a.type == arcangel)
		{
			a.opengl_init(arcangel_image);
		}
		else if (a.type == angel_boat)
		{
			a.opengl_init(angel_boat_image);
		}
		else if (a.type == arcangel_boat)
		{
			a.opengl_init(arcangel_boat_image);
		}
		else if (a.type == angel_fortress)
		{
			a.opengl_init(angel_fortress_image);
		}
		else if (a.type == arcangel_fortress)
		{
			a.opengl_init(arcangel_fortress_image);
		}

		temp_angels.push_back(a);
	}

	size_t demon_count = 0;

	in.read(reinterpret_cast<char*>(&demon_count), sizeof(size_t));

	list<bad_guy> temp_demons;

	for (size_t i = 0; i < demon_count; i++)
	{
		bad_guy d;

		in.read(reinterpret_cast<char*>(&d.mass), sizeof(float));
		in.read(reinterpret_cast<char*>(&d.hit_points), sizeof(long long signed int));
		in.read(reinterpret_cast<char*>(&d.max_hit_points), sizeof(long long unsigned int));
		in.read(reinterpret_cast<char*>(&d.max_damage), sizeof(long long unsigned int));
		in.read(reinterpret_cast<char*>(&d.fish_rate), sizeof(long long unsigned int));
		in.read(reinterpret_cast<char*>(&d.untransformed_location.x), sizeof(float));
		in.read(reinterpret_cast<char*>(&d.untransformed_location.y), sizeof(float));
		in.read(reinterpret_cast<char*>(&d.untransformed_location.z), sizeof(float));
		in.read(reinterpret_cast<char*>(&d.type), sizeof(bad_type));

		if (d.type == demon)
		{
			d.opengl_init(demon_image);
		}
		else if (d.type == arcdemon)
		{
			d.opengl_init(arcdemon_image);
		}
		else if (d.type == demon_boat)
		{
			d.opengl_init(demon_boat_image);
		}
		else if (d.type == arcdemon_boat)
		{
			d.opengl_init(arcdemon_boat_image);
		}
		else if (d.type == demon_fortress)
		{
			d.opengl_init(demon_fortress_image);
		}
		else if (d.type == arcdemon_fortress)
		{
			d.opengl_init(arcdemon_fortress_image);
		}

		temp_demons.push_back(d);
	}

	ld.angels = temp_angels;
	ld.demons = temp_demons;





	return true;
}





void handle_left_mouse_click(int x, int y)
{
	if (state == STATE_LEVEL_WIN)
	{
		curr_level.level_hint++;

		curr_level = levels[curr_level.level_hint];

		for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();

		for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();

		init_level(false);

		level_started_at = std::chrono::high_resolution_clock::now();
		last_refresh_at = level_started_at;
		state = STATE_GAME;
	}
	else if (state == STATE_LEVEL_LOSE)
	{
		curr_level = levels[curr_level.level_hint];


		for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();

		for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();


		init_level(false);


		level_started_at = std::chrono::high_resolution_clock::now();
		last_refresh_at = level_started_at;

		state = STATE_GAME;
	}
	else if (state == STATE_GAME_END)
	{
		curr_level = levels[0];

		for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();

		for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();

		init_level(false);

		level_started_at = std::chrono::high_resolution_clock::now();
		last_refresh_at = level_started_at;
		state = STATE_GAME;

	}
	else if (state == STATE_LITTLE_RED_SPLASH_SCREEN)
	{
		state = STATE_TITLE_SCREEN;
	}
	else if (state == STATE_TITLE_SCREEN)
	{
		if (false == load_from_disk("levels/savegame.bin", curr_level))
		{
			for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
				i->start_time = std::chrono::high_resolution_clock::now();

			for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
				i->start_time = std::chrono::high_resolution_clock::now();

			init_level(false);

			level_started_at = std::chrono::high_resolution_clock::now();
			last_refresh_at = level_started_at;
		}
		else
		{
			for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
				i->start_time = std::chrono::high_resolution_clock::now();

			for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
				i->start_time = std::chrono::high_resolution_clock::now();

			init_level(false);

			level_started_at = std::chrono::high_resolution_clock::now();
			last_refresh_at = level_started_at;
		}

		state = STATE_GAME;

	}
	else if (state == STATE_GAME)
	{
		game_handle_left_mouse_click(x, y);
	}
}




void pause_screen_handle_keys(unsigned char key, int x, int y)
{
	if (tolower(key) == escape_char)
	{
		save_controls_to_disk("settings.txt");

		pause_elapsed = std::chrono::high_resolution_clock::now() - pause_start;

		//ostringstream oss;
		//oss << pause_elapsed.count();
		//SDL_ShowSimpleMessageBox(MB_OK, "title", oss.str().c_str(), gWindow);

		state = STATE_GAME;
		return;
	}
}

int do_quit_messagebox(void)
{
	const SDL_MessageBoxButtonData buttons[] = {
{ /* .flags, .buttonid, .text */        0, 0, "No" },
{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		gWindow, /* .window */
		"?", /* .title */
		"Save before quitting?", /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};

	int button_id = 0;

	SDL_ShowMessageBox(&messageboxdata, &button_id);

	return button_id;
}








bool save_to_disk(const char* const file_name, const level_data& ld)
{
	ofstream out(file_name, ios_base::binary);

	if (out.fail())
		return false;

	out.write(reinterpret_cast<const char*>(&ld.prng_seed), sizeof(long unsigned int));

	out.write(reinterpret_cast<const char*>(&ld.level_hint), sizeof(long unsigned int));

	out.write(reinterpret_cast<const char*>(&ld.good_guy_fish_total), sizeof(long long unsigned int));
	out.write(reinterpret_cast<const char*>(&ld.bad_guy_fish_total), sizeof(long long unsigned int));

	size_t angel_count = ld.angels.size();

	out.write(reinterpret_cast<const char*>(&angel_count), sizeof(size_t));

	for (list<good_guy>::const_iterator i = ld.angels.begin(); i != ld.angels.end(); i++)
	{
		out.write(reinterpret_cast<const char*>(&i->mass), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->hit_points), sizeof(long long signed int));
		out.write(reinterpret_cast<const char*>(&i->max_hit_points), sizeof(long long unsigned int));
		out.write(reinterpret_cast<const char*>(&i->max_damage), sizeof(long long unsigned int));
		out.write(reinterpret_cast<const char*>(&i->fish_rate), sizeof(long long unsigned int));
		out.write(reinterpret_cast<const char*>(&i->untransformed_location.x), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->untransformed_location.y), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->untransformed_location.z), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->type), sizeof(good_type));
	}

	size_t demon_count = ld.demons.size();

	out.write(reinterpret_cast<const char*>(&demon_count), sizeof(size_t));

	for (list<bad_guy>::const_iterator i = ld.demons.begin(); i != ld.demons.end(); i++)
	{
		out.write(reinterpret_cast<const char*>(&i->mass), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->hit_points), sizeof(long long signed int));
		out.write(reinterpret_cast<const char*>(&i->max_hit_points), sizeof(long long unsigned int));
		out.write(reinterpret_cast<const char*>(&i->max_damage), sizeof(long long unsigned int));
		out.write(reinterpret_cast<const char*>(&i->fish_rate), sizeof(long long unsigned int));
		out.write(reinterpret_cast<const char*>(&i->untransformed_location.x), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->untransformed_location.y), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->untransformed_location.z), sizeof(float));
		out.write(reinterpret_cast<const char*>(&i->type), sizeof(bad_type));
	}

	return true;
}













void game_handle_keys(unsigned char key, int x, int y)
{
	if (tolower(key) == escape_char)
	{
		pause_start = std::chrono::high_resolution_clock::now();

		get_controls_from_disk("settings.txt");

		state = STATE_PAUSE_SCREEN;
		return;
	}

	if (tolower(key) == 'd')
	{
		SDL_Keymod s = SDL_GetModState();

		if (s & KMOD_LSHIFT)
		{
			if (developer_mode)
				disable_developer_mode();
			else
				enable_developer_mode();

			level_started_at = std::chrono::high_resolution_clock::now();
			last_refresh_at = level_started_at;
		}

		return;
	}

	if (false == developer_mode)
		return;

	switch (tolower(key))
	{

	case 'z':
	{
		curr_level.good_guy_fish_total = 0;
		break;
	}
	case 'x':
	{
		curr_level.good_guy_fish_total = 5000000;
		break;
	}
	case 'c':
	{
		curr_level.bad_guy_fish_total = 0;
		break;
	}
	case 'v':
	{
		curr_level.bad_guy_fish_total = 5000000;
		break;
	}

	case 'y':
	{
		vertex_3 location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];
		good_guy a;

		a.mass = angel_max_mass;
		a.hit_points = a.max_hit_points = angel_max_hit_points;
		a.untransformed_location = location;
		a.max_damage = angel_max_damage;
		a.type = angel;
		a.fish_rate = angel_fish_rate;
		a.start_time = std::chrono::high_resolution_clock::now();
		a.opengl_init(angel_image);

		curr_level.angels.push_back(a);


		location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];

		a.mass = arcangel_max_mass;
		a.hit_points = a.max_hit_points = arcangel_max_hit_points;
		a.untransformed_location = location;
		a.max_damage = arcangel_max_damage;
		a.type = arcangel;
		a.fish_rate = arcangel_fish_rate;
		a.start_time = std::chrono::high_resolution_clock::now();
		a.opengl_init(arcangel_image);

		curr_level.angels.push_back(a);


		location = ortho_collision_sea_points[mt_rand() % ortho_collision_sea_points.size()];

		a.mass = angel_boat_max_mass;
		a.hit_points = a.max_hit_points = angel_boat_max_hit_points;
		a.untransformed_location = location;
		a.max_damage = angel_boat_max_damage;
		a.type = angel_boat;
		a.fish_rate = angel_boat_fish_rate;
		a.start_time = std::chrono::high_resolution_clock::now();
		a.opengl_init(angel_boat_image);

		curr_level.angels.push_back(a);

		location = ortho_collision_sea_points[mt_rand() % ortho_collision_sea_points.size()];

		a.mass = arcangel_boat_max_mass;
		a.hit_points = a.max_hit_points = arcangel_boat_max_hit_points;
		a.untransformed_location = location;
		a.max_damage = arcangel_boat_max_damage;
		a.type = arcangel_boat;
		a.fish_rate = arcangel_boat_fish_rate;
		a.start_time = std::chrono::high_resolution_clock::now();
		a.opengl_init(arcangel_boat_image);

		curr_level.angels.push_back(a);



		location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];

		a.mass = angel_fortress_max_mass;
		a.hit_points = a.max_hit_points = angel_fortress_max_hit_points;
		a.untransformed_location = location;
		a.max_damage = angel_fortress_max_damage;
		a.type = angel_fortress;
		a.fish_rate = angel_fortress_fish_rate;
		a.start_time = std::chrono::high_resolution_clock::now();
		a.opengl_init(angel_fortress_image);

		curr_level.angels.push_back(a);



		location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];

		a.mass = arcangel_fortress_max_mass;
		a.hit_points = a.max_hit_points = arcangel_fortress_max_hit_points;
		a.untransformed_location = location;
		a.max_damage = arcangel_fortress_max_damage;
		a.type = arcangel_fortress;
		a.fish_rate = arcangel_fortress_fish_rate;
		a.start_time = std::chrono::high_resolution_clock::now();
		a.opengl_init(arcangel_fortress_image);

		curr_level.angels.push_back(a);







		break;
	}
	case 'u':
	{
		vertex_3 location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];
		bad_guy b;

		b.mass = demon_max_mass;
		b.hit_points = b.max_hit_points = demon_max_hit_points;
		b.untransformed_location = location;
		b.max_damage = demon_max_damage;
		b.type = demon;
		b.fish_rate = demon_fish_rate;
		b.start_time = std::chrono::high_resolution_clock::now();
		b.opengl_init(demon_image);

		curr_level.demons.push_back(b);


		location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];

		b.mass = arcdemon_max_mass;
		b.hit_points = b.max_hit_points = arcdemon_max_hit_points;
		b.untransformed_location = location;
		b.max_damage = arcdemon_max_damage;
		b.type = arcdemon;
		b.fish_rate = arcdemon_fish_rate;
		b.start_time = std::chrono::high_resolution_clock::now();
		b.opengl_init(arcdemon_image);

		curr_level.demons.push_back(b);


		location = ortho_collision_sea_points[mt_rand() % ortho_collision_sea_points.size()];

		b.mass = demon_boat_max_mass;
		b.hit_points = b.max_hit_points = demon_boat_max_hit_points;
		b.untransformed_location = location;
		b.max_damage = demon_boat_max_damage;
		b.type = demon_boat;
		b.fish_rate = demon_boat_fish_rate;
		b.start_time = std::chrono::high_resolution_clock::now();
		b.opengl_init(demon_boat_image);

		curr_level.demons.push_back(b);

		location = ortho_collision_sea_points[mt_rand() % ortho_collision_sea_points.size()];

		b.mass = arcdemon_boat_max_mass;
		b.hit_points = b.max_hit_points = arcdemon_boat_max_hit_points;
		b.untransformed_location = location;
		b.max_damage = arcdemon_boat_max_damage;
		b.type = arcdemon_boat;
		b.fish_rate = arcdemon_boat_fish_rate;
		b.start_time = std::chrono::high_resolution_clock::now();
		b.opengl_init(arcdemon_boat_image);

		curr_level.demons.push_back(b);



		location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];

		b.mass = demon_fortress_max_mass;
		b.hit_points = b.max_hit_points = demon_fortress_max_hit_points;
		b.untransformed_location = location;
		b.max_damage = demon_fortress_max_damage;
		b.type = demon_fortress;
		b.fish_rate = demon_fortress_fish_rate;
		b.start_time = std::chrono::high_resolution_clock::now();
		b.opengl_init(demon_fortress_image);

		curr_level.demons.push_back(b);



		location = ortho_collision_island_points[mt_rand() % ortho_collision_island_points.size()];

		b.mass = arcdemon_fortress_max_mass;
		b.hit_points = b.max_hit_points = arcdemon_fortress_max_hit_points;
		b.untransformed_location = location;
		b.max_damage = arcdemon_fortress_max_damage;
		b.type = arcdemon_fortress;
		b.fish_rate = arcdemon_fortress_fish_rate;
		b.start_time = std::chrono::high_resolution_clock::now();
		b.opengl_init(arcdemon_fortress_image);

		curr_level.demons.push_back(b);







		break;
	}


	case 'n':
		{
			if (levels.size() <= curr_level.level_hint)
				return;

			long unsigned int lh = curr_level.level_hint;

			if (lh > 0)
			{
				lh--;

				curr_level = levels[lh];
				curr_level.level_hint = lh;

				for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
					i->start_time = std::chrono::high_resolution_clock::now();

				for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
					i->start_time = std::chrono::high_resolution_clock::now();

				init_level(false);

				level_started_at = std::chrono::high_resolution_clock::now();
				last_refresh_at = level_started_at;
			}

			return;
		}

	case 'm':
		{
			if (levels.size() <= curr_level.level_hint)
				return;

			long unsigned int lh = curr_level.level_hint;

			if (lh < levels.size() - 1)
			{
				lh++;

				curr_level = levels[lh];
				curr_level.level_hint = lh;

				for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
					i->start_time = std::chrono::high_resolution_clock::now();

				for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
					i->start_time = std::chrono::high_resolution_clock::now();

				init_level(false);

				level_started_at = std::chrono::high_resolution_clock::now();
				last_refresh_at = level_started_at;

			}

			break;
		}




	case 's':
	{
		ostringstream oss;
		oss << curr_level.prng_seed;

		save_to_disk(oss.str().c_str(), curr_level);
		break;
	}
	case 'p':
	{
		curr_level.prng_seed = static_cast<long unsigned int>(time(0));
		init_level(true);
		break;
	}

	case 'k':
	{
		for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
			i->hit_points = i->max_hit_points;

		break;
	}
	case 'l':
	{
		for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
			i->hit_points = i->max_hit_points;

		break;
	}


	case 'w':
	{
		good_guy_mode = !good_guy_mode;
		break;
	}
	case '0':
	{
		if (good_guy_mode)
			g_type = angel_none;
		else
			b_type = demon_none;

		break;
	}
	case '1':
	{
		if (good_guy_mode)
			g_type = angel;
		else
			b_type = demon;

		break;
	}

	case '2':
	{
		if (good_guy_mode)
			g_type = arcangel;
		else
			b_type = arcdemon;

		break;
	}

	case '3':
	{
		if (good_guy_mode)
			g_type = angel_boat;
		else
			b_type = demon_boat;

		break;
	}
	case '4':
	{
		if (good_guy_mode)
			g_type = arcangel_boat;
		else
			b_type = arcdemon_boat;

		break;
	}

	case '5':
	{
		if (good_guy_mode)
			g_type = angel_fortress;
		else
			b_type = demon_fortress;

		break;
	}

	case '6':
	{
		if (good_guy_mode)
			g_type = arcangel_fortress;
		else
			b_type = arcdemon_fortress;

		break;
	}


	default:
		break;
	}

}

void handle_keys(unsigned char key, int x, int y)
{
	if (state == STATE_GAME)
	{
		game_handle_keys(key, x, y);
	}
	else if (state == STATE_PAUSE_SCREEN)
	{
		pause_screen_handle_keys(key, x, y);
	}
}





bool parse_levels(const char* const filename)
{
	levels.clear();

	ifstream infile(filename);

	if (infile.fail())
		return false;

	string line;

	while (getline(infile, line))
	{
		if (line == "")
			continue;

		string level_file_name = line;

		level_data ld;

		if (false == load_from_disk(level_file_name.c_str(), ld))
		{
			levels.resize(0);
			return false;
		}

		levels.push_back(ld);
	}

	if (levels.size() == 0)
	{
		return false;
	}
	else
	{
		for (unsigned long int i = 0; i < levels.size(); i++)
			levels[i].level_hint = i;
	}

	level_data ld;

	if (true == load_from_disk("levels/savegame.bin", ld))
	{
		curr_level = ld;

		if (curr_level.prng_seed != levels[curr_level.level_hint].prng_seed)
		{
//			ostringstream oss;
//			oss << curr_level.level_hint << " " << curr_level.prng_seed << " " << levels[curr_level.level_hint].prng_seed;

			SDL_ShowSimpleMessageBox(0, "Error", "PRNG seed mismatch", gWindow);

			return false;
		}
		else
		{
			curr_level = levels[ld.level_hint];

			for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
				i->start_time = std::chrono::high_resolution_clock::now();

			for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
				i->start_time = std::chrono::high_resolution_clock::now();

			init_level(false);

			level_started_at = std::chrono::high_resolution_clock::now();
			last_refresh_at = level_started_at;
		}
	}
	else
	{
		curr_level = levels[0];
		curr_level.level_hint = 0;

		for (list<good_guy>::iterator i = curr_level.angels.begin(); i != curr_level.angels.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();

		for (list<bad_guy>::iterator i = curr_level.demons.begin(); i != curr_level.demons.end(); i++)
			i->start_time = std::chrono::high_resolution_clock::now();

		init_level(false);

		level_started_at = std::chrono::high_resolution_clock::now();
		last_refresh_at = level_started_at;
	}

	return true;
}






#endif