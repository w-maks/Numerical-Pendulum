#include "pendulum.h"
#include <math.h>

const double g = 9.81;
const double R = 1.0;
const double m = 1.0;

void pendulum_derivatives(double t, double* s, double* k)
{
    k[0] = s[1];
    k[1] = -g / R * sin(s[0] * M_PI / 180);
}

double T(double omega) {
    return 0.5 * m * pow(R, 2) * pow(omega, 2);
}

double U(double phi) {
    return -m * g * R * cos(phi*M_PI/180);
}

double E(double T, double U) {
    return T + U;
}