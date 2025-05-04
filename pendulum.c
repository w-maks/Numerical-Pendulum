#include "pendulum.h"
#include <math.h>

const double g = 9.81;
const double R = 1.0;
const double m = 1.0;

void pendulum_derivatives(double t, double* s, double* k)
{
    k[0] = s[1];
    k[1] = -g / R * sin(s[0]);
}

double T(const double omega) {
    return 0.5 * m * pow(R, 2) * pow(omega, 2);
}

double U(const double phi) {
    return -m * g * R * cos(phi);
}

double E(const double T, const double U) {
    return T + U;
}

void period_reset(PeriodDetector* pd, const double omega0) {
    pd->crossings = 0;
    pd->omega_previous = omega0;
    pd->t_previous = 0.0;
    pd->t_crossing[0] = pd->t_crossing[1] = 0.0;
}

double period_update(PeriodDetector* pd, const double t, const double omega) {
    if (pd->omega_previous < 0.0 && omega > 0.0) {
        //linear interpolation of omega==0 moment
        const double frac = pd->omega_previous / (pd->omega_previous - omega);
        const double t0 = pd->t_previous + frac * (t - pd->t_previous);

        if (pd->crossings < 2)
            pd->t_crossing[pd->crossings] = t0;

        pd->crossings++;
        //period as time between two successive maxima
        if (pd->crossings == 2) {
            return pd->t_crossing[1] - pd->t_crossing[0];
        }
    }
    pd->omega_previous = omega;
    pd->t_previous = t;
    return NAN;
}