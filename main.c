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

    FILE *fp2 = fopen("periods.csv", "w");
    fprintf(fp2, "phi0,period\n");

    for (size_t j = 0; j < 5; ++j) {
        double t = 0.0;
        s[0] = phi0[j] * M_PI / 180;
        s[1] = omega0;

        PeriodDetector pd;
        period_reset(&pd, omega0);
        double period_found = NAN;

        FILE *fp = fopen(files[j], "w");

        if (j == 0) {
            fprintf(fp, "t,phi,omega,phi_anal,omega_anal,T,U,E\n");
            for (int i = 0; i <= N; ++i) {
                analytical_pendulum(t, phi0[j] * M_PI / 180, omega0, a);
                fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",t, s[0], s[1], a[0], a[1], T(s[1]), U(s[0]), E(T(s[1]), U(s[0])));

                double period = period_update(&pd, t, s[1]);
                if (!isnan(period) && isnan(period_found)) {
                    period_found = period;
                }

                rk4_vec(t, dt, n, s, f);
                t += dt;
            }
        } else {
            fprintf(fp, "t,phi,omega,T,U,E\n");
            for (int i = 0; i <= N; ++i) {
                fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf\n", t, s[0], s[1], T(s[1]), U(s[0]), E(T(s[1]), U(s[0])));

                double period = period_update(&pd, t, s[1]);
                if (!isnan(period) && isnan(period_found)) {
                    period_found = period;
                }

                rk4_vec(t, dt, n, s, f);
                t += dt;
            }
        }

        fprintf(fp2, "%lf,%lf\n", phi0[j], period_found);

        fclose(fp);
    }

    fclose(fp2);
    free(a);
    free(s);
    return 0;
}
