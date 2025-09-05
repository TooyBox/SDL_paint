#include <include/inputs.h>
#include <include/gui.h>
#include <include/brushes.h>
#include <string.h>
#include <stdio.h>

void mouse_input(SDL_Event event) {
	Point cursor = (Point) {(double)event.motion.x, (double)event.motion.y};

	C.Hovering = (cursor.x < 101) ? INTERFACE : CANVAS;

	get_Hovering(event, cursor);

	if (C.Held == BRUSH) {
		brush(event, cursor);
	}
	else if (C.Held == ERASER) {
		eraser(event, cursor);
	}
}


void key_input(SDL_Event event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_C:
				clear_canvas();
				break;
			case SDLK_B:
				C.Held = BRUSH;
				break;
			case SDLK_E:
				C.Held = ERASER;
				break;
		}
	}	
}

/* GUI detection, collisions. Need to make a lil nicer :D */
void get_Hovering(SDL_Event event, Point cursor) {
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		GUI object = get_hovering_collision_object(cursor);
		if (object.name == NULL) return;
		else if (strcmp(object.name, "BRUSH") == 0) {
			C.Held = BRUSH;
		}
		else if (strcmp(object.name, "ERASER") == 0) {
			C.Held = ERASER;
		}
		else if (strcmp(object.name, "COLOR_PICKER") == 0) {
			C.Color = color_picker(cursor, NULL);
		}
		else if (strcmp(object.name, "HUE_PICKER") == 0) {
			Uint8 ret[3];
			color_picker(cursor, ret);
			GUI_color_picker(ret);
		}
	}
}


void clear_canvas() {
	SDL_Rect c = (SDL_Rect) {101, 0, 799, 600};
	SDL_FillSurfaceRect(USR_Canvas, &c, Canv.color);
}