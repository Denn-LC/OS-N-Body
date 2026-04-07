#include <math.h>
#include <stdio.h>

#define G 1.0         // gravitational constant, is 6.67*10^-11 N*m^2/kg^2 in reality
#define DT 0.01       // timestep
#define STEPS 1000    // total number of calculations performed per run
#define SOFTENING 0.1 // so forces dont blow up at dist = 0 to infinity

int main(void) {
    // body 1
    double x1 = -1.0, y1 = 0.0;
    double vx1 = 0.0, vy1 = 0.5;
    double m1 = 1.0;

    // body 2
    double x2 = 1.0, y2 = 0.0;
    double vx2 = 0.0, vy2 = -0.5;
    double m2 = 1.0;

    double E_initial = 0.0;

    for (int i = 0; i < STEPS; i++) {

        double dx = x2 - x1;
        double dy = y2 - y1;

        double dist = sqrt(dx * dx + dy * dy + SOFTENING * SOFTENING);

        double force = G * m1 * m2 / (dist * dist);

        double ax1 = force * dx / dist / m1;
        double ay1 = force * dy / dist / m1;
        double ax2 = -force * dx / dist / m2;
        double ay2 = -force * dy / dist / m2;

        // total kinetic energy of system = (1/2)*(m)*(v^2) note, velocity is the total magnitude of
        // components
        double ke = (0.5 * m1 * (vx1 * vx1 + vy1 * vy1)) + (0.5 * m2 * (vx2 * vx2 + vy2 * vy2));
        // total potential energy of the system = -(G*M*m)/r note, this is hardcoded for 2 bodies
        double pe = -G * m1 * m2 / dist;
        // total energy of the system
        double energy = ke + pe;

        if (i == 0) {
            E_initial = energy;
        }

        double drift = energy - E_initial;
        // check if energy is being conserved
        if (fabs(drift) > 0.01 * fabs(E_initial)) { // if drift is bigger the  1% of the inital
            printf("Energy is not being conserved");
            break;
        }

        vx1 += ax1 * DT;
        vy1 += ay1 * DT;
        vx2 += ax2 * DT;
        vy2 += ay2 * DT;

        x1 += vx1 * DT;
        y1 += vy1 * DT;
        x2 += vx2 * DT;
        y2 += vy2 * DT;

        printf("step %4d  body1=(%.3f, %.3f)  body2=(%.3f, %.3f)\n", i, x1, y1, x2, y2);
    }
    return 0;
}