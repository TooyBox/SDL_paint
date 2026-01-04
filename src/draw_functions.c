#include <include/draw_functions.h>
#include <math.h>

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

