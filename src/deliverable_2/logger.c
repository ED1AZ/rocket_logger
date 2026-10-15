#include <stdio.h>
#include "main.h"

// gravity constant
const double G = 9.81;
// define constants using values from deliverable 1 example
#define INITIAL_ALTITUDE 0.0
#define INITIAL_VELOCITY 0.0
#define INITIAL_FUEL 50
#define A_THRUST 15
#define DT 0.1
#define MAX_STEPS 300

// determine what the next acceleration and fuel remaining for the rocket 
void update_sensor_sample(sensor_sample_s *sensor) {
     // increment timestamp
    sensor->timestamp += DT;

    // acceleration is dependent on fuel amount
    if (sensor->fuel > 0) { 
        sensor->acceleration = A_THRUST - G;
        sensor->fuel -= 1; // fuel depleted each step
    } else sensor->acceleration = -G;
}

// take a sensor sample and calculate velocity and altitude
void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry) {
    telemetry->velocity += sensor->acceleration * DT;        
    telemetry->altitude += telemetry->velocity * DT;
}

static rocket_state state;
void run_rocket_state(const telemetry_packet_s *telemetry) {
    switch (state) {
        case FLIGHT_ASCENT:

            break;
        case FLIGHT_COAST:
            break;
        case FLIGHT_DESCENT:
            break;
        case FLIGHT_LANDED:
            break;
    }

    if (telemetry->altitude > 0) {
        if (telemetry->sensor->fuel > 0 && telemetry->velocity > 0) {
            state = FLIGHT_ASCENT;
            printf("ascending");
        } else if (telemetry->sensor->fuel == 0 && telemetry->velocity > 0) {
            state = FLIGHT_COAST;
            printf("coasting");
        } else {
            state = FLIGHT_DESCENT;
            printf("descending");
        }
    } else {
        // altitude = 0
        state = FLIGHT_LANDED;
        printf("landed");
    }
}



int main() {
    // variable declarations
    double z0 = INITIAL_ALTITUDE, v0 = INITIAL_VELOCITY, fuel = INITIAL_FUEL, a_thrust = A_THRUST, dt = DT;
    const int max_steps = MAX_STEPS;
    double altitude_history[max_steps];
    double max_altitude = INITIAL_ALTITUDE;
    int steps = 0;

        while (state != FLIGHT_LANDED) {
        // update sensor sample
        }

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