#include "main.h"

int main(int argc, char** argv)
{
	last_refresh_at = std::chrono::high_resolution_clock::now();

	if (!init())
		return 1;

	playMusicFromMemory(music, global_volume);

	SDL_Surface* surface = SDL_LoadBMP("media/icon.bmp");
	SDL_SetWindowIcon(gWindow, surface);
	SDL_FreeSurface(surface);

	bool quit = false;

	SDL_Event e;

	SDL_StartTextInput();

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				if (state == STATE_GAME || state == STATE_PAUSE_SCREEN)
				{
					if (false == draw_level_end_banner)
					{
						if (1 == do_quit_messagebox())
							save_to_disk("levels/savegame.bin", curr_level);

						quit = true;
						break; // immediately stop polling for events
					}
					else
					{
						if (1 == do_quit_messagebox2())
						{
							quit = true;
							break; // immediately stop polling for events
						}
					}
				}
				else if(state == STATE_LEVEL_WIN || state == STATE_LEVEL_LOSE || state == STATE_GAME_END)
				{
					if (1 == do_quit_messagebox2())
					{
						quit = true;
						break; // immediately stop polling for events
					}
				}
				else
				{
					quit = true;
					break; // immediately stop polling for events
				}
			}
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) 
			{
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);

				handle_keys(escape_char, x, y);
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);

				handle_keys(e.text.text[0], x, y);
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					int x = e.button.x;
					int y = e.button.y;

					handle_left_mouse_click(x, y);
				}
			}
			else if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					win_x = e.window.data1;
					win_y = e.window.data2;

					glViewport(0, 0, win_x, win_y);
				}
			}
		}
		
		if (!quit)
		{
			idle_func();
			display_func();

			SDL_GL_SwapWindow(gWindow);
		}
	}

	SDL_StopTextInput();

	close();

	return 0;
}