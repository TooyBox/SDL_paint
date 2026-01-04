#ifndef INPUTS_H
#define INPUTS_H

#include <include/model.h>

void mouse_input(SDL_Event event);
void key_input(SDL_Event event);
void get_Hovering(SDL_Event event, Point cursor);
void clear_canvas();

#endif
