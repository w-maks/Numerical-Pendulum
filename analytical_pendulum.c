#include "analytical_pendulum.h"
#include "pendulum.h"
#include <math.h>

double* analytical_pendulum(const double t, const double phi0, const double omega0, double* a)
{
    const double phi0_rad = phi0 * M_PI / 180.0;
    const double omega = sqrt(g / R);

    const double phi_phase = atan(-omega0 / phi0_rad / omega);
    const double A = phi0_rad / cos(phi_phase);

    a[0] = A * cos(omega * t + phi_phase);
    a[1] = -A * omega * sin(omega * t + phi_phase);

    return a;
}
