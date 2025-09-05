#ifndef GUI_H
#define GUI_H

#include <include/model.h>

void init_GUI();
void set_hue_picker();
void GUI_color_picker(Uint8 vals[3]);
Uint32 color_picker(Point p, Uint8 *ret);

#endif