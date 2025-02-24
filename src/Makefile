CC=gcc
CFLAGS= -Wall -pedantic -Wextra -std=c99
CPPFLAGS= -g

.PHONY: all clean

CODE=main.c
OBJS=main.o

INCLUDE=-Ix86_64-w64-mingw32/include -I.

LIB=-Lx86_64-w64-mingw32/lib -lSDL3 -L.

EXEC= main

all: $(EXEC)

clean:
	rm -rf $(EXEC) $(OBJS)

main.o : main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c -o main.o $(INCLUDE)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LIB)
