#include <include/gui.h>

/* Hard coded locations for each GUI element, easiest way? 
	Should base off of window size */ // maybe idek
GUI create_gui_element(char * name, int x, int y, int width, int height, Uint32 color, bool draw) {
	SDL_Rect rect = (SDL_Rect) {x, y, width, height};
	if (draw == true) {
		SDL_FillSurfaceRect(USR_Canvas, &rect, color);
	}
	GUI g = (GUI) {name, width, height, x, y, color, rect};
	return g;
}

/* Located at x = (10, 90), y = (190, 400)*/
void GUI_color_picker(Uint8 vals[3]) {
	double r = 255.0, g = 255.0, b = 255.0;
	double my, mx, change[3];
	double temp[3];

	int i, j;
	Uint32 color;

	mx = 255.0 / 80.0;
	my = 255.0 / 210.0;

	for (i = 0; i < 3; i++) {
		if (vals[i] == 255.0) {
			change[i] = 0;
		}
		else if (vals[i] != 0) {
			change[i] = mx - (vals[i] / 80.0);
		}
		else {
			change[i] = mx; 
		}
	}

	for (i = 10; i <= 90; i++) {		
		temp[0] = r;
		temp[1] = g;
		temp[2] = b;

		for (j = 190; j <= 400; j++) {
			color = SDL_MapRGB(SDL_GetPixelFormatDetails(USR_Canvas->format), NULL, \
					(Uint8) temp[0], \
				       	(Uint8) temp[1], \
				       	(Uint8) temp[2]);
			SDL_Rect rect = (SDL_Rect) {i, j, 1, 1};
			SDL_FillSurfaceRect(USR_Canvas, &rect, color);
			temp[0] = ((temp[0] - my) > 0) ? (temp[0] - my) : (0);
			temp[1] = ((temp[1] - my) > 0) ? (temp[1] - my) : (0);
			temp[2] = ((temp[2] - my) > 0) ? (temp[2] - my) : (0);
		}
		r -= change[0];
		g -= change[1];
		b -= change[2];
	}
}

Uint32 color_picker(Point p, Uint8 *ret) {
	Uint8 val[3];
	SDL_ReadSurfacePixel(USR_Canvas, \
			p.x, p.y, \
			&val[0], \
		       	&val[1], \
			&val[2], \
			NULL);
	if ( ret != NULL ) {
		SDL_ReadSurfacePixel(USR_Canvas, \
			p.x, p.y, \
			&ret[0], \
		       	&ret[1], \
			&ret[2], \
			NULL);
	}
	return SDL_MapSurfaceRGB(USR_Canvas, val[0], val[1], val[2]);
}

/* Located at x = (10, 90), y = (410, 450)*/
void set_hue_picker() {
	Uint32 color;

	int x = 10, y = 410;
	int i, j, k = 2, factor;
	
	double vals[3] = {255.0, 0.0, 0.0};
	double mx = 80.0 / 3.0;

	for (i = x; i <= 90; i++) {
		for (j = y; j <= 450; j++) {
			color = SDL_MapSurfaceRGB(USR_Canvas, (Uint8) vals[0], \
				       	(Uint8) vals[1], (Uint8) vals[2]);
			SDL_Rect rect = (SDL_Rect) {i, j, 1, 1};
			SDL_FillSurfaceRect(USR_Canvas, &rect, color);
		}
		if (vals[k%3] <= 0.0) {
			factor = 1;
		} 
		else if (vals[k%3] >= 255.0) { 
			factor = -1;
		}

		vals[k%3] += (factor * mx);
		if (vals[k%3] >= 255.0) {
			vals[k%3] = 255.0;
			k++;
		}
		else if (vals[k%3] <= 0.0) {
			vals[k%3] = 0.0;
			k++;
		}
	}

}

void init_GUI() {
	init_gui_collisions(10);

	Uint8 vals[] = {255, 0, 0};
	Grap = create_gui_element("GUI", 100, 600, 0, 0, COLOR_BLACK, true);
	Canv = (Canvas) {799, 600, 101, 0, COLOR_WHITE};

	append_collision_object(create_gui_element("CANVAS", 101, 0, 799, 600, COLOR_WHITE, true));
	append_collision_object(create_gui_element("BRUSH", 10, 10, 80, 80, COLOR_BLUE, true));
	append_collision_object(create_gui_element("ERASER", 10, 100, 80, 80, COLOR_RED, true));

	append_collision_object(create_gui_element("COLOR_PICKER", 10, 190, 80, 210, 0, false));
	append_collision_object(create_gui_element("HUE_PICKER", 10, 410, 80, 40, 0, false));

	GUI_color_picker(vals);
	set_hue_picker();

	SDL_UpdateWindowSurface(window);
}