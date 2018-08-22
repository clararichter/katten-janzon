//https://wiki.libsdl.org/CategoryAPI

#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include "complex.h"
#include "color.h"

Uint8 color_black_and_white(int iterations);
int iterations(complex c);
void update_pixels(SDL_Renderer* renderer);

#define MAX( a, b ) ( ( a > b) ? a : b )
#define MIN( a, b ) ( ( a < b) ? a : b )

const int FPS = 45;

const int MAX_ITER = 256;
const double WIDTH = 900;
const double HEIGHT = 700;
double X_MIN = -2.0;
double X_MAX = 2.0;
double Y_MIN = -2.0;
double Y_MAX = 2.0;
double ESCAPE_BOUND = 2;

double start_c = 0.0;
double end_c = 2.0;


Uint8 color_black_and_white(int iterations){
  if(iterations % 2)
    return 0;
  else
    return 255;
}

Uint8 color_grayscale(int iterations){
  if(iterations >= MAX_ITER - 1)
    return 0;
  else
    return iterations;
}


/*
Given a complex number c, calculate the number of iterations needed to achieve a Zn = (Zn-1)^2 + c such that Zn > 2.
If max_iteration is reached, it is assumed that the sequence will never exceed 2 and thus belongs to the Mandelbrot set.
*/
int iterations(complex c){
  complex z;
  int iteration;

  z.real = 0;
  z.imag = 0;
  iteration = 0;
  while( c_squared_modulus(z) < ESCAPE_BOUND*ESCAPE_BOUND && iteration < MAX_ITER ){
    z = c_add( c_multiply(z, z), c );
    iteration += 1;
  }
  return iteration;
}


void update_pixels(SDL_Renderer* renderer){

      complex c;
      int color;
      for(int x = 0; x < WIDTH; x++)
        for(int y = 0; y < HEIGHT; y++){
          // Rescale and realign
          c.real = ( ( (double)x/WIDTH ) * (X_MAX-X_MIN) ) + X_MIN;
          c.imag = ( ( (double)y/HEIGHT ) * (Y_MAX-Y_MIN) ) + Y_MIN;

          color = color_black_and_white(iterations(c));
          SDL_SetRenderDrawColor( renderer, color, color, color, 255 );
          SDL_RenderDrawPoint(renderer, x, y);
        }
}


/*
Given a complex number c, calculate the number of iterations needed to achieve a Zn = (Zn-1)^2 + c such that Zn > 2.
If max_iteration is reached, it is assumed that the sequence will never exceed 2 and thus belongs to the Mandelbrot set.
*/
int julia_iterations(double zx, double zy, complex c){
  int iteration;
  iteration = 0;
  double xtemp;
  while( zx*zx + zy*zy < ESCAPE_BOUND*ESCAPE_BOUND && iteration < MAX_ITER ){
    xtemp = zx*zx - zy*zy;
    zy = 2*zx*zy  + c.imag;
    zx = xtemp + c.real;
    iteration += 1;
  }
  return iteration;
}

void update_pixels_julia(SDL_Renderer* renderer, complex c){

      int color;
      complex z;
      for(int x = 0; x < WIDTH; x++)
        for(int y = 0; y < HEIGHT; y++){
          // Rescale and realign
          z.real = ( ( (double)x/WIDTH ) * (X_MAX-X_MIN) ) + X_MIN;
          z.imag = ( ( (double)y/HEIGHT ) * (Y_MAX-Y_MIN) ) + Y_MIN;

          color = color_black_and_white(julia_iterations(z.real, z.imag, c));
          SDL_SetRenderDrawColor( renderer, color, color, color, 255 );
          SDL_RenderDrawPoint(renderer, x, y);
        }
}

complex funny(double a){
   complex c;
   c.real = 0.7885 * exp(-a);
   c.imag = 0;
   return c;

}

double normalized(double v, double old_s, double old_e, double new_s, double new_e){
  return ( ( (v - old_s) / (old_e - old_s) ) * (new_e - new_s) ) + new_s;
}



int main (int argc, char **argv)
{
    // Setup
    SDL_Window* window;
    window = SDL_CreateWindow(
        "Julia Set Animator", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );
    // Setup
    SDL_Renderer* renderer;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    update_pixels(renderer);
    SDL_RenderPresent(renderer);

    int running = 1;
    while (running){
        // Get the next event
        SDL_Event event;
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
              break;

        }
        // Make sure the right amount of time has passed

        update_pixels_julia(renderer, funny(normalized( SDL_GetTicks() % 15000, 0, 15000, 0, M_PI)));
        SDL_RenderPresent(renderer);
    }

    return EXIT_SUCCESS;
}
