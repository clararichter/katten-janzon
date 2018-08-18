CC = gcc
CFLAGS = -Wall -O2 `sdl2-config --cflags --libs`

main: main.o complex.o
	$(CC) -o program main.o complex.o $(CFLAGS)
