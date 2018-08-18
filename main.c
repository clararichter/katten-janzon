#include <SDL.h>
#include "complex.h"

const int max_iterations = 256;
const double width = 720;
const double height = 500;


/*
Given a complex number c, calculate the number of iterations needed to achieve a Zn = (Zn-1)^2 + c such that Zn > 2.
If max_iteration is reached, it is assumed that the sequence will never exceed 2 and thus belongs to the Mandelbrot set.
*/
int iterations(complex c){
  complex z;
  z.real = 0;
  z.imag = 0;
  for(int i = 0; i<max_iterations; i++){
    z = c_add( c_multiply(z, z), c );
    if( c_absolute(z) > 4.0 )
      return i;
  }
  return max_iterations;
}

/*

*/
Uint8 getColor(int iterations){
  if(iterations >= max_iterations - 1)
    return 0;
  else
    return 255;
}

int main (int argc, char** argv)
{
    // Setup window
    SDL_Window* window;
    window = SDL_CreateWindow(
        "Mandelbrot", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    complex c;
    int color;
    for(int x = 0; x < width; x++)
      for(int y = 0; y < height; y++){
        //normalize
        c.real = ((double)x - width) / width;
        c.imag = ((double)y - height) / height;

        color = getColor(iterations(c));
        SDL_SetRenderDrawColor( renderer, color, color, color, 255 );
        SDL_RenderDrawPoint(renderer, x, y);
      }


    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    // Wait for 5 sec
    SDL_Delay( 2000 );
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
