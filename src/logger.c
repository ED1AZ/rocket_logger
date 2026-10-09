#include <stdio.h>

// gravity constant
const float G = 9.81;

int main() {
    // get user input
    float z0, v0, fuel, a_thrust, dt, a;
    int max_steps;
    printf("Enter v0 (m/s): ");
    scanf("%f", &v0);
    printf("Enter initial fuel (steps): ");
    scanf("%f", &fuel);
    printf("Enter engine accel a_thrust (m/s^2): ");
    scanf("%f", &a_thrust);
    printf("Enter dt (s): ");
    scanf("%f", &dt);
    printf("Enter max steps: ");
    scanf("%d", &max_steps);

    double altitude_history[max_steps];
    double max_altitude = 0;
    // loop based on max_steps
    for (int i = 0; i < max_steps; i++) {
        altitude_history[i] = z0;

        // update max altitude during flight
        if (z0 > max_altitude) {
            max_altitude = z0;
        }
        
        // acceleration is dependent on fuel amount
        if (fuel > 0) { 
            a = a_thrust - G;
        } else a = -G;

        // update position and velocity
        z0 += v0 * dt;
        v0 += a * dt;
        fuel -= 1; // fuel depleted each step

    }

    return 0;
}