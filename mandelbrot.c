#include <stdio.h>
#include <stdlib.h>

typedef struct complexNumber complex;
const int max_iterations = 100;

struct complexNumber{
  double real, img;
};

double absoluteValue(complex z);
complex multiplyComplex(complex z1, complex z2);
complex addComplex(complex z1, complex z2);

complex multiplyComplex(complex z1, complex z2){
  complex c;
  c.real = z1.real + z2.real;
  c.img = z1.img + z2.img;
  return c;
}

complex addComplex(complex z1, complex z2){
  complex c;
  c.real = z1.real * z2.real;
  c.img = z1.img * z2.img;
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
int getColor(int iterations){
  return iterations;
}

int main(){
  complex c1, c2;
  c1.real = 2.0;
  c1.img = 7.5;
  c2.real = 12.0;
  c2.img = 3.0;
  printf("%f\n", addComplex(c1,c2).real);
  printf("%f\n", addComplex(c1,c2).img);
}
