#include "rk4.h"
#include "pendulum.h"
#include "analytical_pendulum.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    const int n = 2;
    const double dt = 0.01;
    const int N = 1000;
    const double phi0[] = {4, 45, 90, 135, 175};
    const double omega0 = 0.0;

    double *s = malloc(n * sizeof *s);
    double *a = malloc(n * sizeof *a);

    void (*f)(double,double*,double*) = pendulum_derivatives;

    const char *files[] = {"pendulum_4.csv", "pendulum_45.csv", "pendulum_90.csv", "pendulum_135.csv", "pendulum_175.csv"};

    for (size_t j = 0; j < 5; ++j) {
        double t = 0.0;
        s[0] = phi0[j] * M_PI / 180;
        s[1] = omega0;
        FILE *fp = fopen(files[j], "w");
        if (j == 0) {
            fprintf(fp, "t,phi,omega,phi_anal,omega_anal\n");
            for (int i = 0; i <= N; ++i) {
                analytical_pendulum(t, phi0[j] * M_PI / 180, omega0, a);
                fprintf(fp, "%lf,%lf,%lf,%lf,%lf\n",t, s[0], s[1], a[0], a[1]);
                rk4_vec(t, dt, n, s, f);
                t += dt;
            }
        } else {
            fprintf(fp, "t,phi,omega,T,U,E\n");
            for (int i = 0; i <= N; ++i) {
                fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf\n", t, s[0], s[1], T(s[1]), U(s[0]), E(T(s[1]), U(s[0])));
                rk4_vec(t, dt, n, s, f);
                t += dt;
            }
        }
        fclose(fp);
    }

    free(a);
    free(s);
    return 0;
}
