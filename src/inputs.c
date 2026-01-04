#include <include/inputs.h>
#include <include/gui.h>
#include <include/brushes.h>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <include/stb_image_write.h>

#include <string.h>
#include <stdio.h>
#define CHANNEL_NUM 3

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

Uint8 *read_from_canvas() {
	int x = 100, y = 0, i = 0, j = 1, w = 2;

	Uint8 *pixels = malloc(sizeof(Uint8) * CHANNEL_NUM * (Canv.W + 100) * Canv.H);
	if (pixels == NULL) {
		printf("Failed to allocate memory for reading canvas pixels.\n");
		return NULL;
	}

	for (y = 0; y < Canv.H; y++) {
		for (x = 100; x < (Canv.W + 100); x++) {
			SDL_ReadSurfacePixel(USR_Canvas, \
					x, y, \
					&pixels[i], \
					&pixels[j], \
					&pixels[w], \
					NULL);
			i += 3; j += 3; w += 3;
		}
	}
	return pixels;
}


void save_canvas(const char *filename) {
	Uint8 *pixels = read_from_canvas();
	if (pixels == NULL) {
		printf("Failed to read pixels from canvas.\n");
		return;
	}
	int result = stbi_write_png(filename, Canv.W, Canv.H, CHANNEL_NUM, pixels, Canv.W * CHANNEL_NUM);
	if (result) {
		printf("Saved canvas to %s\n", filename);
	} else {
		printf("Failed to save canvas to %s\n", filename);
	}
	free(pixels);
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
			case SDLK_S:
				save_canvas("output.png");
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
