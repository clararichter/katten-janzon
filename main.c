#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include "complex.h"
#include "color.h"

#define LINEAR_INTERPOLATE( c1, c2, t) ( c1*t + c2*(1-t) )
#define NORMALIZE(value, old_range_start, old_range_end, new_range_start, new_range_end) ( ( ( (value - old_range_start) / (old_range_end - old_range_start) ) * (new_range_end - new_range_start) ) + new_range_start)


const int MAX_ITER = 1000;
const double WIDTH = 900;
const double HEIGHT = 700;
double X_MIN = -1.5;
double X_MAX = 1.5;
double Y_MIN = -1.5;
double Y_MAX = 1.5;
double ESCAPE_BOUND = 2;
int PALETTE_SIZE = 17;
RGB_Color PALETTE[] = {{.r = 66,  .g = 30,  .b = 15},
                        {.r = 25,  .g = 7,   .b = 26},
                        {.r = 9,   .g = 1,   .b = 47},
                        {.r = 4,   .g = 4,   .b = 73},
                        {.r = 0,   .g = 7,   .b = 100},
                        {.r = 12,  .g = 44,  .b = 138},
                        {.r = 24,  .g = 82,  .b = 177},
                        {.r = 57,  .g = 125, .b = 209},
                        {.r = 134, .g = 181, .b = 229},
                        {.r = 211, .g = 236, .b = 248},
                        {.r = 241, .g = 233, .b = 191},
                        {.r = 248, .g = 201, .b = 95},
                        {.r = 255, .g = 170, .b = 0},
                        {.r = 204, .g = 128, .b = 0},
                        {.r = 153, .g = 87,  .b = 0},
                        {.r = 106, .g = 52,  .b = 3},
                        {.r = 66,  .g = 30,  .b = 15}};


int iterations(complex z, complex c){
  int iteration;
  iteration = 0;
  while( c_squared_modulus(z) < ESCAPE_BOUND*ESCAPE_BOUND && iteration < MAX_ITER ){
    z = c_add( c_multiply(z, z), c );
    iteration += 1;
  }
  return iteration;
}

void update_pixels(SDL_Renderer* renderer, complex c){
      complex z;
      int iter;
      int color_index;
      RGB_Color c1;
      RGB_Color c2;
      for(int x = 0; x < WIDTH; x++)
        for(int y = 0; y < HEIGHT; y++){
          z.real = ( ( (double)x/WIDTH ) * (X_MAX-X_MIN) ) + X_MIN;
          z.imag = ( ( (double)y/HEIGHT ) * (Y_MAX-Y_MIN) ) + Y_MIN;
          iter = iterations(z, c);
          color_index = iter % (PALETTE_SIZE - 1);
          c1 = PALETTE[color_index];
          c2 = PALETTE[color_index + 1];
          SDL_SetRenderDrawColor( renderer, (int)LINEAR_INTERPOLATE( c1.r, c2.r, 0.25 ), (int)LINEAR_INTERPOLATE( c1.g, c2.g, 0.25 ), (int)LINEAR_INTERPOLATE( c1.b, c2.b, 0.25 ), 255 );
          SDL_RenderDrawPoint(renderer, x, y);
        }
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

    complex c;
    c.real = 0.386015;
    c.imag = 0.140758;

    // TODO: make animation smooth
    int running = 1;
    while (running){
        // Get the next event
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
              running = 0;
        }
        if(!running) break;

        // Make sure the right amount of time has passed
        c.real += 0.00015;
        c.imag += 0.00015;
        update_pixels(renderer, c);
        SDL_RenderPresent(renderer);
    }

    return EXIT_SUCCESS;
}
