#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define G 1.0         // gravitational constant, is 6.67*10^-11 N*m^2/kg^2 in reality
#define DT 0.01       // timestep
#define STEPS 1000    // total number of calculations performed per run
#define SOFTENING 0.1 // so forces dont blow up at dist = 0 to infinity
#define MAX_BODIES 10 // maximum amount of bodies before throwing a warning

typedef struct {
    double x;
    double y;
} vec2_t;

typedef struct {
    vec2_t pos;
    vec2_t vel;
    vec2_t acc;
    double mass;
} body_t;

double rand_range(double min, double max) {
    return min + (rand() / (double)RAND_MAX) * (max - min);
}

int init_bodies(body_t bodies[], int *n) {
    printf("Select a scenario:\n");
    printf("1. Two-body orbit\n");
    printf("2. Three-body system\n");
    printf("3. Figure-8 orbit\n");
    printf("4. Entropymaxxing\n");
    printf("Enter choice: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        // two body orbit
        *n = 2;
        bodies[0].pos = (vec2_t){0.0, 0.0};
        bodies[0].vel = (vec2_t){0.0, 0.0};
        bodies[0].mass = 1000.0;
        bodies[1].pos = (vec2_t){10.0, 0.0};
        bodies[1].vel = (vec2_t){0.0, 10.0};
        bodies[1].mass = 1.0;
        return 1;
    } else if (choice == 2) {
        // three body system
        *n = 3;
        bodies[0].pos = (vec2_t){0.0, 0.0};
        bodies[0].vel = (vec2_t){0.0, 0.0};
        bodies[0].mass = 1000.0;
        bodies[1].pos = (vec2_t){10.0, 0.0};
        bodies[1].vel = (vec2_t){0.0, 10.0};
        bodies[1].mass = 1.0;
        bodies[2].pos = (vec2_t){-10.0, 0.0};
        bodies[2].vel = (vec2_t){0.0, -10.0};
        bodies[2].mass = 1.0;
        return 2;
    } else if (choice == 3) {
        // figure-8
        *n = 3;
        bodies[0].pos = (vec2_t){0.9700436, -0.2430875};
        bodies[0].vel = (vec2_t){0.4662036, 0.4323657};
        bodies[0].mass = 1.0;
        bodies[1].pos = (vec2_t){-0.9700436, 0.2430875};
        bodies[1].vel = (vec2_t){0.4662036, 0.4323657};
        bodies[1].mass = 1.0;
        bodies[2].pos = (vec2_t){0.0, 0.0};
        bodies[2].vel = (vec2_t){-0.9324072, -0.8647314};
        bodies[2].mass = 1.0;
        return 3;
    } else if (choice == 4) {
        *n = 2 + rand() % 9; //  random range between [2-10]
        // entropy maxxing
        for (int i = 0; i < *n; i++) {
            bodies[i].pos.x = rand_range(-20.0, 20.0);
            bodies[i].pos.y = rand_range(-20.0, 20.0);
            bodies[i].vel.x = rand_range(-8.0, 8.0);
            bodies[i].vel.y = rand_range(-8.0, 8.0);
            bodies[i].mass = rand_range(1.0, 200.0);
        }
        return 4;
    } else {
        printf("Invalid choice\n");
        *n = 0;
        return 0;
    }
}
void compute_forces(body_t bodies[], int n) {
    // zero acceleration from last frame so forces dont blow up
    for (int i = 0; i < n; i++) {
        bodies[i].acc.x = 0.0;
        bodies[i].acc.y = 0.0;
    }
    // calcuate forces on each body every step
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = bodies[j].pos.x - bodies[i].pos.x;
            double dy = bodies[j].pos.y - bodies[i].pos.y;
            double r2 = dx * dx + dy * dy + SOFTENING * SOFTENING;
            double inv_r3 = G / (r2 * sqrt(r2));

            bodies[i].acc.x += inv_r3 * bodies[j].mass * dx;
            bodies[i].acc.y += inv_r3 * bodies[j].mass * dy;
            bodies[j].acc.x -= inv_r3 * bodies[i].mass * dx;
            bodies[j].acc.y -= inv_r3 * bodies[i].mass * dy;
        }
    }
}

double compute_energy(body_t bodies[], int n) {
    double energy = 0.0;
    for (int i = 0; i < n; i++) {
        double v2 = bodies[i].vel.x * bodies[i].vel.x + bodies[i].vel.y * bodies[i].vel.y;
        energy += 0.5 * bodies[i].mass * v2;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = bodies[j].pos.x - bodies[i].pos.x;
            double dy = bodies[j].pos.y - bodies[i].pos.y;
            double r = sqrt(dx * dx + dy * dy + SOFTENING * SOFTENING);
            energy -= G * bodies[i].mass * bodies[j].mass / r;
        }
    }
    return energy;
}

void integrate(body_t bodies[], int n) {
    for (int i = 0; i < n; i++) {
        bodies[i].vel.x += bodies[i].acc.x * DT;
        bodies[i].vel.y += bodies[i].acc.y * DT;
        bodies[i].pos.x += bodies[i].vel.x * DT;
        bodies[i].pos.y += bodies[i].vel.y * DT;
    }
}

void print_state(body_t bodies[], int n, int step) {
    for (int i = 0; i < n; i++) {
        printf("x: %.4f y: %.4f @ step: %d\n", bodies[i].pos.x, bodies[i].pos.y, step);
    }
}

int main(void) {
    body_t bodies[MAX_BODIES];

    srand(time(NULL)); // randomness for entropymaxxing

    int n = 0;
    int choice = init_bodies(bodies, &n);
    if (n == 0) {
        return 0;
    }

    double E_initial = 0.0;

    for (int i = 0; i < STEPS; i++) {
        compute_forces(bodies, n);
        integrate(bodies, n);
        double energy = compute_energy(bodies, n);

        if (i == 0) {
            E_initial = energy;
        }

        double drift = energy - E_initial;
        if (choice != 4) {
            if (fabs(drift) >
                0.01 * fabs(E_initial)) { // if drift is bigger then 1% of inital energy
                printf("warning: energy isnt being conserved %.2f%% at step %d\n",
                       100.0 * drift / fabs(E_initial), i);
                break;
            }
        }

        print_state(bodies, n, i);
    }
    if (choice == 4) {
        printf("note: energy is not conserved for entropymaxxing, this is due to the limitations of Euler integration");
    }
    return 0;
}
