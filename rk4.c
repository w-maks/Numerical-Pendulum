#include "rk4.h"

void rk4_vec(const double t, const double dt, const int n, double* s,
             void (*f)(double, double*, double*))
{
    #define M 1000
    static double k1[M], k2[M], k3[M], k4[M], w[M];

    for (int i =0; i < n ; i++) w [i]= s [i];
    f(t, w, k1);

    for (int i = 0; i < n; i++) w[i] = s[i] + 0.5 * dt * k1[i];
    f(t + 0.5 * dt, w, k2);

    for (int i = 0; i < n; i++) w[i] = s[i] + 0.5 * dt * k2[i];
    f(t + 0.5* dt, w, k3);

    for (int i = 0; i < n; i++) w[i] = s[i] + dt * k3[i];
    f(t + dt, w, k4);

    for (int i = 0; i < n; i++) s[i] += dt / 6.0 * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
}
