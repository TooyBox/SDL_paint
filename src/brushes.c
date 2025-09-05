#include <include/brushes.h>
#include <include/draw_functions.h>

void brush(SDL_Event event, Point cursor) {
	static bool is_prev = false;
	static Point prev;

	if (event.type == SDL_EVENT_MOUSE_MOTION && event.motion.state != 0) {
		if (!is_prev) {
			is_prev = true;
			prev = cursor;
		}
		draw_line(prev, cursor, C.Color, 2);
		prev = cursor;
	}
	else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		prev = cursor;
		draw_point(cursor, C.Color, 2);
		is_prev = true;
	} else { 
		is_prev = false;
	}
}

void eraser(SDL_Event event, Point cursor) {
	static bool is_prev = false;
	static Point prev;

	if (event.type == SDL_EVENT_MOUSE_MOTION && event.motion.state != 0) {
		if (!is_prev) {
			is_prev = true;
			prev = cursor;
		}
		draw_line(prev, cursor, Canv.color, 10);
		prev = cursor;
	}
	else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		prev = cursor;
		draw_point(cursor, Canv.color, 10);
		is_prev = true;
	} else { 
		is_prev = false;
	}

}
