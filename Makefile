CC = gcc
CFLAGS = `sdl2-config --cflags --libs`

main: main.c
	$(CC) -o yay main.c $(CFLAGS)

mandelbrot: mandelbrot.c
	$(CC) -o mandel mandelbrot.c $(CFLAGS)
