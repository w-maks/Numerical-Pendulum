#ifndef PENDULUM_H
#define PENDULUM_H

extern const double g;
extern const double R;
extern const double m;

void pendulum_derivatives(double t, double* s, double* k);

double T(double omega);

double U(double phi);

double E(double T, double U);

typedef struct {
    int crossings;
    double omega_previous;
    double t_previous;
    double t_crossing[2];
} PeriodDetector;

void period_reset(PeriodDetector* pd, double omega0);
double period_update(PeriodDetector* pd, double t, double omega);

#endif