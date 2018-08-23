#include <stdio.h>
#include "complex.h"

int MAX_ITER = 15;

int iterations(complex c){
  printf("c = %.2f + %.2fi\n\n", c.real, c.imag);

  complex z;
  int iteration;

  z.real = 0;
  z.imag = 0;
  iteration = 0;
  printf("i = 0 ____ z = %.2f + %.2fi ____ absolute value squared: %.2f\n", z.real, z.imag, c_squared_modulus(z));
  while( iteration < MAX_ITER ){
    z = c_add( c_multiply(z, z), c );
    iteration += 1;
    printf("i = %d ____ z = %.2f + %.2fi ____ absolute value squared: %.2f\n", iteration, z.real, z.imag, c_squared_modulus(z));
  }
  return iteration;
}

int main(){
  complex c;
  c.real = 0.5;
  c.imag = -0.1;
  iterations(c);
}
