#include <stdio.h>

// gravity constant
const double G = 9.81;

int main() {
    // get user input
    double z0, v0, fuel, a_thrust, dt, a;
    int max_steps;
    printf("Enter z0 (m): ");
    scanf("%lf", &z0);
    printf("Enter v0 (m/s): ");
    scanf("%lf", &v0);
    printf("Enter initial fuel (steps): ");
    scanf("%lf", &fuel);
    printf("Enter engine accel a_thrust (m/s^2): ");
    scanf("%lf", &a_thrust);
    printf("Enter dt (s): ");
    scanf("%lf", &dt);
    printf("Enter max steps: ");
    scanf("%d", &max_steps);

    double altitude_history[max_steps + 1];
    double max_altitude = 0;
    int steps = 0;

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
            fuel -= 1; // fuel depleted each step
        } else a = -G;

        // update position, velocity, steps
        v0 += a * dt;        
        z0 += v0 * dt;
        steps = i + 1;

        // touchdown with clamp
        if (z0 <= 0 && v0 <= 0) {
            z0 = 0;              
            break;
        }
    }

    // store final altitude and check for max altitude (if max_steps is hit while climbing)
    altitude_history[max_steps] = z0;            
    if (z0 > max_altitude) max_altitude = z0;    

    // print results
    printf("--- Rocket Telemetry ---\n");
    printf("Steps: %d Total time: %.1f s\n", steps, steps * dt);
    printf("Max altitude: %.1f m\n", max_altitude);
    printf("Final altitude: %.1f m\n", z0);
    printf("Final velocity: %.1f m/s\n", v0);
    printf("Fuel remaining: %.1f\n", fuel);
    printf("Altitude history (every 10 steps): ");
    for (int i = 0; i <= steps; i += 10) {
        printf("%.2f, ", altitude_history[i]);
    }

    return 0;
}