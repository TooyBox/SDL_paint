#include <include/model.h>
#include <stdlib.h>
#include <stdio.h>

SDL_Window *window;
SDL_Surface *USR_Canvas;

Cursor C;
Canvas Canv;
GUI Grap;

int Width = 900;
int Height = 600;

GUI *collisions;
unsigned int collisions_cursor = 0;

GUI get_hovering_collision_object(Point cursor) {
    unsigned int i;
    for (i = 0; i < collisions_cursor; i++) {
        if ((cursor.x >= collisions[i].x) && (cursor.x <= (collisions[i].x + collisions[i].W))) {
            if ((cursor.y >= collisions[i].y) && (cursor.y <= (collisions[i].y + collisions[i].H))) {
                printf("Hovering over %s element at index %d\n", collisions[i].name, i);
                return collisions[i];
            }
        }
    }
    return (GUI) {NULL, 0, 0, 0, 0, 0, {0, 0, 0, 0}};
}

void append_collision_object(GUI g) {
    collisions[collisions_cursor] = g;
    collisions_cursor++;
    printf("Appended GUI collision object at index %d\n", collisions_cursor - 1);
}

void init_gui_collisions(int num) {
    collisions = malloc(num * sizeof(GUI));
    if (collisions == NULL) {
        printf("Failed to allocate memory for GUI collision objects.\n");
        exit(-1);
    }
}

void free_gui_objects() {
    free(collisions);
    collisions = NULL;
    collisions_cursor = 0;
}