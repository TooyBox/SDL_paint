#ifndef draw_functions_h
#define draw_functions_h

#include <include/model.h>

void draw_point(Point p, Uint32 color, int size);
void draw_line(Point p1, Point p2, Uint32 color, int size);
void draw_circle(Point p, double radius, Uint32 color, int size);
void draw_box(Point p1, Point p2, Uint32 color, int size);

#endif
