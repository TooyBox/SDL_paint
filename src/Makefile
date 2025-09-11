#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:SDL_Paint")

CC=gcc
CFLAGS= -Wall -pedantic -Wextra -std=c99
CPPFLAGS= -g

.PHONY: all clean

OBJS=$(BUILD_DIR)\main.o $(BUILD_DIR)\model.o $(BUILD_DIR)\draw_functions.o $(BUILD_DIR)\inputs.o $(BUILD_DIR)\gui.o $(BUILD_DIR)\brushes.o

INCLUDE=-I.

LIB=-L. -lSDL3

BUILD_DIR=build

EXEC= SDL_Paint

all: $(EXEC)

clean:
	rd -r $(EXEC) $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LIB)

$(BUILD_DIR)\main.o : main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c -o $(BUILD_DIR)\main.o $(INCLUDE)

$(BUILD_DIR)\model.o : model.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c model.c -o $(BUILD_DIR)\model.o $(INCLUDE)

$(BUILD_DIR)\inputs.o : inputs.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c inputs.c -o $(BUILD_DIR)\inputs.o $(INCLUDE)

$(BUILD_DIR)\gui.o : gui.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c gui.c -o $(BUILD_DIR)\gui.o $(INCLUDE)

$(BUILD_DIR)\brushes.o : brushes.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c brushes.c -o $(BUILD_DIR)\brushes.o $(INCLUDE)

$(BUILD_DIR)\draw_functions.o : draw_functions.c | $(BUILD_DIR)
	$(CC) -mwindows $(CFLAGS) $(CPPFLAGS) -c draw_functions.c -o $(BUILD_DIR)\draw_functions.o $(INCLUDE)
