#ifndef _COMPLEX_HEADER_FILE_
#define _COMPLEX_HEADER_FILE_

struct ComplexNumber {
  double real, imag;
};

typedef struct ComplexNumber complex;

double c_squared_modulus(complex z);
complex c_add(complex c1, complex c2);
complex c_multiply(complex c1, complex c2);
#endif
