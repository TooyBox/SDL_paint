#define _USE_MATH_DEFINES

#include <include/model.h>
#include <include/draw_functions.h>
#include <include/inputs.h>
#include <include/gui.h>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef WINDOWS
#include <windows.h>
#endif

void init_window(const char *name, int w, int h) {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(name, w, h, 0x0);
	USR_Canvas = SDL_GetWindowSurface(window);
}

int main(void) {
	#ifdef WINDOWS
	  FreeConsole();
	#endif
	init_window("Bob", Width, Height);
	init_GUI();

	bool running = 1;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = 0;
				free_gui_objects();
				printf("Goodbye...\n");
				return 0;
			}
			if (event.type >= 0x400 && event.type < 0x600) {
				mouse_input(event);
			}
		        if (event.type >= 0x300 && event.type < 0x400) {
				key_input(event);
			}	
		}
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}
}
