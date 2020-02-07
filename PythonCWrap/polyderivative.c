#include <stdio.h>
#include <math.h>

float poly(const float a[], const unsigned, const float);
float deriv(const float a[], const unsigned, const float);
float integ(const float a[], const unsigned, const float, const float);
void printpoly(const float a[], const unsigned, const float);

int polynomialderivativeintegral() {
  float x, *a, y1, dy1, iy1;
  int junk;
  unsigned deg, i;

  printf("Enter the degree of polynomial equation: ");
  junk = scanf("%d", &deg);

  printf("Ehter the value of x for which the equation is to be evaluated: ");
  junk = scanf("%f", &x);

  a = (float *)malloc(sizeof(float) * deg);

  for(i=0;i<=deg;i++) {
    printf("Enter the coefficient of x^%d: ",i);
    scanf("%f",&a[i]);
  }
  printpoly(a, deg, x);
  y1 = poly(a, deg, x);
  dy1 = deriv(a, deg, x);
  iy1 = integ(a, deg, x, 0);
  printf("The value of polynomial equation for the value of x = %.2f is: %.2f",x,y1);
  printf("\nThe value of the derivative of the polynomial equation at x = %.2f is: %.2f\n",x,dy1);
  printf("\nThe value of the integral of the polynomial equation at x = %.2f is: %.2f\n",x,iy1);
  free(a);
  return 0;
}

float poly(const float a[], const unsigned deg, const float x) {
  float sum = 0;
  unsigned i = 0;
  for(;i<=deg;++i)
    sum += pow(a[i], i);
  return sum;
}

float deriv(const float a[], const unsigned deg, const float x) {
  float sum = 0, ps;
  unsigned i = 0;
  for(; i <= deg; ++i)
    sum += (deg-i)*a[deg-i]*(float)pow(x, deg-(i+1));
  return sum;
}

float integ(const float a[], const unsigned deg, const float x, const float x_)  {
  float sum = 0, ps;
  unsigned i = x_;
  for (; i <= deg; ++i) {
    ps = (float)pow(x, (double)deg+1-i);
    sum += (a[deg-i]*ps)/(deg+1-i);
  }
  return sum;
}

void printpoly(const float a[], const unsigned deg, const float x) {
  int i;
  printf("FUNCTION: ");
  for (i = 0; i <= deg; ++i) {
    printf("%.2fx^%d ", a[i], i);
    if (i < deg) printf("+ ");
  }
  printf("\n");
}