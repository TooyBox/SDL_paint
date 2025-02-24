#define _USE_MATH_DEFINES
#include <SDL3/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
#define COLOR_WHITE 0xffffffff
#define COLOR_RED 0xeb220d
#define COLOR_BLUE 0x10a2e3
#define COLOR_GREEN 0x7be12a
#define COLOR_BLACK 0x00000000

typedef enum {
	BRUSH,
	ERASER,
	BOX
} Cursor_type;

typedef enum {
	CANVAS,
	INTERFACE
} Bounds;

typedef struct {
	double x;
	double y;
} Point;

typedef struct {
	Point P;
	Uint32 Color;
	Cursor_type Held;
	Bounds Hovering;
	int size;
} Cursor;


typedef struct {
	int W; /* total Width of object */
	int H; /* total Height of object */
	int x; /* starting x coords; */
	int y; /* starting y coords; */
	Uint32 color;
} Canvas;

typedef struct {
	int W; /* total Width of object */
	int H; /* total Height of object */
	int x; /* starting x coords; */
	int y; /* starting y coords; */
	Uint32 color;
} GUI;


SDL_Window *window;
SDL_Surface *USR_Canvas;

Cursor C;
Canvas Canv;
GUI Grap;


int W = 900;
int H = 600;


void draw_point(Point p, Uint32 color, int size) {
	if (p.x > 100) {
		SDL_Rect rect = (SDL_Rect) {p.x, p.y, size, size};
		SDL_FillSurfaceRect(USR_Canvas, &rect, color);
	}
}

void draw_line(Point p1, Point p2, Uint32 color, int size) {
	double factor = 0, i, j;
	double slope, b, s;
	Point curr;

	if (p1.x == p2.x && p1.y == p2.y) {
		draw_point(p1, color, size);
		return;
	}

	/* verticle line */
	if (p1.x == p2.x) {
		i = p1.y;
		curr.x = p1.x;
		factor = (p1.y > p2.y) ? -1.0 : 1.0;

		while (i != p2.y) {
			curr.y = i;
			draw_point(curr, color, size); 
			i += factor;
		}
		return;
	}
	/* horizontal line */
	else if (p1.y == p2.y) {
		i = p1.x;
		curr.y = p1.y;
		factor = (p1.x > p2.x) ? -1.0 : 1.0;

		while (i != p2.x) {
			curr.x = i;
			draw_point(curr, color, size);
			i += factor;
		}
		return;
	}
	/* sloped line */
	else {
		i = p1.x;
		slope = (p2.y - p1.y) / (p2.x - p1.x);
		b = p1.y - (slope * p1.x);
		factor = (p1.x > p2.x) ? -1.0 : 1.0;
		j = (p1.y > p2.y) ? -1.0 : 1.0;
		while (i != p2.x) {
			curr.y = (slope * i) + b;
			curr.x = i;
			draw_point(curr, color, size);
			s = fabs(slope);
			while (s > 0) {
				curr.y += j;
				draw_point(curr, color, size);
				s--;
			}
			i += factor;
		}
	}
}


void draw_circle(Point p, double radius, Uint32 color, int size) {
	Point curr;
	int counter = 360;
	int j = (int)radius;

	while (j > 0) {
		while (counter > 0) {
			curr.x = p.x + (double)j * cos(((double)counter) * M_PI/180);
			curr.y = p.y + (double)j * sin(((double)counter) * M_PI/180);
			draw_point(curr, color, size);
			counter-=30;
		}
		counter = 360;
		j--;
	}
}


void funslope() {
	/*
	i = p1.x;
	slope = (p1.x - p2.x) / (p1.y - p2.y);
	b = p1.y - (slope * p1.x);
	factor = (p1.x > p2.x) ? -1.0 : 1.0;

	while ((i += factor) != p2.x) {
		curr.y = (slope * i) + b;
		curr.x = (curr.y - b) / slope;
		draw_point(curr, COLOR_GREEN, size);
	}
	return;
	*/
}

void draw_box(Point p1, Point p2, Uint32 color, int size) {
	Point p3, p4;

	if (p1.x == p2.x || p1.y == p2.y) {
		draw_line(p1, p2, color, size);
	} else {
		p3 = (Point) {p2.x, p1.y};
		p4 = (Point) {p1.x, p2.y};

		draw_line(p1, p3, color, size);
		draw_line(p3, p2, color, size);
		draw_line(p2, p4, color, size);
		draw_line(p4, p1, color, size);
	}
}



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

void GUI_color_picker(Uint8 vals[3]) {
	double r = 255.0, g = 255.0, b = 255.0;
	double my, change[3];
	double temp[3];

	int i, j;
	Uint32 color;

	for (i = 0; i < 3; i++) {
		if (vals[i] != 0) {
			change[i] = 255 / (double) vals[i];
		} else {
			change[i] = 0;
		}
	}

	my = 255.0 / 210.0;

	for (i = 10; i <= 90; i++) {
		temp[0] = r;
		temp[1] = g;
		temp[2] = b;
		for (j = 190; j <= 400; j++) {
			temp[0] = ((temp[0] - my) > 0) ? (temp[0] - my) : (0);
			temp[1] = ((temp[1] - my) > 0) ? (temp[1] - my) : (0);
			temp[2] = ((temp[2] - my) > 0) ? (temp[2] - my) : (0);

			color = SDL_MapRGB(SDL_GetPixelFormatDetails(USR_Canvas->format), NULL, \
					(Uint8) temp[0], \
				       	(Uint8) temp[1], \
				       	(Uint8) temp[2]);
			SDL_Rect rect = (SDL_Rect) {i, j, 1, 1};
			SDL_FillSurfaceRect(USR_Canvas, &rect, color);
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


void get_Hovering(SDL_Event event, Point cursor) {
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (cursor.x >= 10 && cursor.x <= 90) {
			if (cursor.y >= 10 && cursor.y <= 90) {
				printf("Brush\n");
				C.Held = BRUSH;
			}
			if (cursor.y >= 100 && cursor.y <= 180) {
				printf("Eraser\n");
				C.Held = ERASER;
			}
			if (cursor.y >= 190 && cursor.y <= 400) {
				printf("Color\n");
				C.Color = color_picker(cursor, NULL);
			}
			if (cursor.y >= 410 && cursor.y <= 450) {
				printf("Hue\n");
				Uint8 *ret = (Uint8*) malloc(sizeof(Uint8) * 3);
				color_picker(cursor, ret);
				GUI_color_picker(ret);
				free(ret);
			}
		}
	}
}


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

void init_GUI() {
	Uint8 vals[] = {255, 0, 0};
	Grap = (GUI) {100, 600, 0, 0, COLOR_BLACK};
	Canv = (Canvas) {799, 600, 101, 0, COLOR_WHITE};

	SDL_Rect g = (SDL_Rect) {0, 0, 100, 600};
	SDL_Rect c = (SDL_Rect) {101, 0, 799, 600};
	SDL_Rect b = (SDL_Rect) {10, 10, 80, 80};
	SDL_Rect e = (SDL_Rect) {10, 100, 80, 80};

	SDL_FillSurfaceRect(USR_Canvas, &g, Grap.color);
	SDL_FillSurfaceRect(USR_Canvas, &b, COLOR_BLUE);
	SDL_FillSurfaceRect(USR_Canvas, &e, COLOR_RED);	
	SDL_FillSurfaceRect(USR_Canvas, &c, Canv.color);

	GUI_color_picker(vals);
	set_hue_picker();

	SDL_UpdateWindowSurface(window);
}

void clear_canvas() {
	SDL_Rect c = (SDL_Rect) {101, 0, 799, 600};
	SDL_FillSurfaceRect(USR_Canvas, &c, Canv.color);
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


void init_window(const char *name, int w, int h) {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(name, w, h, 0x0);
	USR_Canvas = SDL_GetWindowSurface(window);
}

int main(void) {
	init_window("Bob", 900, 600);
	init_GUI();

	bool running = 1;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = 0;
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
