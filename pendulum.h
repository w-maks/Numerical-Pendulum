#ifndef PENDULUM_H
#define PENDULUM_H

extern const double g;
extern const double R;
extern const double m;

void pendulum_derivatives(double t, double* s, double* k);

double T(double omega);

double U(double phi);

double E(double T, double U);

#endif