#include <math.h>
#include <stdio.h>

#define G 1.0         // gravitational constant, is 6.67*10^-11 N*m^2/kg^2 in reality
#define DT 0.01       // timestep
#define STEPS 1000    // total number of calculations performed per run
#define SOFTENING 0.1 // so forces dont blow up at dist = 0 to infinity
#define MAX_BODIES 10 // maximum amount of bodies before throwing a warning

void init_bodies(double x[], double y[], double vx[], double vy[], double m[], int *n) {
    scanf("%d", n);
    if (*n > MAX_BODIES) { // throw warning if n is bigger then 10
        printf("Performance may suffer when N > 10 do you want to continue?\n");
        printf("y/n: ");
        char yn;
        scanf(" %c", &yn);
        if (yn == 'n') {
            *n = 0;
            return;
        }
    }
    for (int i = 0; i < *n; i++) {
        // ins code
    }
}

void compute_forces(double x[], double y[], double m[], double ax[], double ay[], int n) {
}

double compute_energy(double x[], double y[], double vx[], double vy[], double m[], int n) {
}

void integrate(double x[], double y[], double vx[], double vy[], double ax[], double ay[], int n) {
}

void print_state(double x[], double y[], int n, int step) {
    for (int i = 0; i < n; i++) {
        printf("x: %.4f y: %.4f @ step: %d\n", x[i], y[i], step);
    }
}

int main(void) {
    double x[MAX_BODIES], y[MAX_BODIES];
    double vx[MAX_BODIES], vy[MAX_BODIES];
    double m[MAX_BODIES];
    double ax[MAX_BODIES], ay[MAX_BODIES];
    int n = 0;

    init_bodies(x, y, vx, vy, m, &n);

    double E_initial = 0.0;

    for (int i = 0; i < STEPS; i++) {
        compute_forces(x, y, m, ax, ay, n);
        integrate(x, y, vx, vy, ax, ay, n);
        double energy = compute_energy(x, y, vx, vy, m, n);

        if (i == 0) {
            E_initial = energy;
        }

        double drift = energy - E_initial;
        if (fabs(drift) > 0.01 * fabs(E_initial)) { // if drift is bigger then 1% of inital energy
            printf("WARNING: energy isnt being conserved %.4f at step %d\n",
                   100.0 * drift / fabs(E_initial), i);
            break;
        }

        print_state(x, y, n, i);
    }
    return 0;
}
