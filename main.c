#include <SDL.h>

typedef struct complexNumber complex;
typedef struct color color;

const int max_iterations = 500;
const double width = 1000;
const double height = 1000;

struct complexNumber{
  double real, img;
};

struct color{
  Uint8 r, g, b;
};

double absoluteValue(complex z);
complex multiplyComplex(complex z1, complex z2);
complex addComplex(complex z1, complex z2);

complex multiplyComplex(complex z1, complex z2){
  complex c;
  c.real = ( z1.real * z2.real ) - ( z1.img * z2.img );
  c.img = ( z1.real * z2.img ) + ( z1.img * z2.real );
  return c;
}

complex addComplex(complex z1, complex z2){
  complex c;
  c.real = z1.real + z2.real;
  c.img = z1.img + z2.img;
  return c;
}

/*
Given a complex number c, calculate the number of iterations needed to achieve a Zn = (Zn-1)^2 + c such that Zn > 2.
If max_iteration is reached, it is assumed that the sequence will never exceed 2 and thus belongs to the Mandelbrot set.
*/
int iterations(complex c){
  complex z;
  z.real = 0;
  z.img = 0;
  for(int i = 0; i<max_iterations; i++){
    z = addComplex( multiplyComplex(z, z), c );
    if( absoluteValue(z) > 4.0 )
      return i;
  }
  return max_iterations;
}

double absoluteValue(complex z){
  return (z.real * z.real) + (z.img * z.img);
}

/*

*/
color getColor(int iterations){
  color c;
  if(iterations >= 499){
    c.r = 0;
    c.g = 0;
    c.b = 0;

  }
  else{
    c.r = 255;
    c.g = 255;
    c.b = 255;

  }
  return c;
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
    color pixel;
    int iter;
    for(int x = 0; x < width; x++)
      for(int y = 0; y < height; y++){
        //normalize
        c.real = ((double)x - width) / width;
        c.img = ((double)y - height) / height;
        //printf("R: %f, I: %f\n", c.real, c.img);

        iter = iterations(c);
        //printf("%d", iter);
        pixel = getColor(iter);
        SDL_SetRenderDrawColor( renderer, pixel.r, pixel.g, pixel.b, 255 );
        SDL_RenderDrawPoint(renderer, x, y);
      }


    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    // Wait for 5 sec
    SDL_Delay( 10000 );
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
