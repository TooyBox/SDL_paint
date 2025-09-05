#ifndef MODEL_H
#define MODEL_H

//May cause issues with including SDL headers in other files
#include <SDL3/SDL.h>

#ifndef basic_defines
#define basic_defines
    #define M_PI 3.14159265358979323846
    #define COLOR_WHITE 0xffffffff
    #define COLOR_RED 0xeb220d
    #define COLOR_BLUE 0x10a2e3
    #define COLOR_GREEN 0x7be12a
    #define COLOR_BLACK 0x00000000
#endif

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
	char * name;
	int W; /* total Width of object */
	int H; /* total Height of object */
	int x; /* starting x coords; */
	int y; /* starting y coords; */
	Uint32 color;
	SDL_Rect rect;
} GUI;


extern SDL_Window *window;
extern SDL_Surface *USR_Canvas;

extern Cursor C;
extern Canvas Canv;
extern GUI Grap;


extern int Width;
extern int Height;

GUI get_hovering_collision_object(Point cursor);

void append_collision_object(GUI g);

void init_gui_collisions(int num);
void free_gui_objects();

#endif