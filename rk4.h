#ifndef RK4_H
#define RK4_H

void rk4_vec(double t, double dt, int n, double *s,
             void (*f)(double, double*, double*));

#endif