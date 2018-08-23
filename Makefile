CC = gcc
CFLAGS = -Wall -O2 -g `sdl2-config --cflags --libs`

main: main.o complex.o
	$(CC) -o program main.o complex.o -lm $(CFLAGS)

exp: explorer.o complex.o
	$(CC) -o exp explorer.o complex.o
