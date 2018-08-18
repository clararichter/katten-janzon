#include "complex.h"

complex c_multiply(complex z1, complex z2){
  complex c;
  c.real = ( z1.real * z2.real ) - ( z1.imag * z2.imag );
  c.imag = ( z1.real * z2.imag ) + ( z1.imag * z2.real );
  return c;
}

complex c_add(complex z1, complex z2){
  complex c;
  c.real = z1.real + z2.real;
  c.imag = z1.imag + z2.imag;
  return c;
}


double c_absolute(complex z){
  return (z.real * z.real) + (z.imag * z.imag);
}
