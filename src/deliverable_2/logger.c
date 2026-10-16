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
    telemetry->sensor = *sensor;
    telemetry->velocity += sensor->acceleration * DT;        
    telemetry->altitude += telemetry->velocity * DT;

    // clamping altitude and velocity
    if (telemetry->altitude <= 0) {
        telemetry->altitude = 0;
        if (telemetry->velocity < 0) telemetry->velocity = 0;
    }
}

// initial state of the rocket is prelaunch
static rocket_state state = FLIGHT_PRELAUNCH;
void run_rocket_state(const telemetry_packet_s *telemetry) {
    switch (state) {
        // previously, state was initialized to FLIGHT_LANDED, but this makes the while loop not run
        // did not initialize state to FLIGHT_ASCENT in case there is not enough fuel
        // so, added FLIGHT_PRELAUNCH state to check if flight is able to lift off
        case FLIGHT_PRELAUNCH:
            if (telemetry->altitude > 0) {
                state = FLIGHT_ASCENT;
                printf("ascending\n");
            } else if (telemetry->sensor.fuel <= 0) {
                // never going to lift off if not enough fuel
                state = FLIGHT_LANDED;
                printf("failed to launch\n");
            }
            break;
        case FLIGHT_LANDED:
            if (telemetry->altitude > 0) {
                state = FLIGHT_ASCENT;
                printf("ascending");
            }
            break;
        case FLIGHT_ASCENT:
            if (telemetry->sensor.fuel <= 0 && telemetry->velocity > 0) {
                state = FLIGHT_COAST;
                printf("coasting");
            }
            break;
        case FLIGHT_COAST:
            if (telemetry->velocity <= 0) {
                state = FLIGHT_DESCENT;
                printf("descending");
            }
            break;
        case FLIGHT_DESCENT:
            if (telemetry->altitude <= 0) {
                state = FLIGHT_LANDED;
                printf("landed");
            }
            break;
        default:
            printf("Error: Invalid rocket state\n");
            break;
    }
}



int main() {
    // variable declarations
    double z0 = INITIAL_ALTITUDE, v0 = INITIAL_VELOCITY, fuel = INITIAL_FUEL, a_thrust = A_THRUST, dt = DT;
    const int max_steps = MAX_STEPS;
    double altitude_history[max_steps];
    double max_altitude = INITIAL_ALTITUDE;
    int steps = 0;

    sensor_sample_s sensor = {0.0, INITIAL_FUEL, 0.0};
    telemetry_packet_s telemetry = {sensor, INITIAL_VELOCITY, INITIAL_ALTITUDE};

    while (state != FLIGHT_LANDED && steps < max_steps) {
        update_sensor_sample(&sensor);
        update_telemetry_state(&sensor, &telemetry);
        run_rocket_state(&telemetry);

        if (telemetry.altitude > max_altitude) max_altitude = telemetry.altitude;
        if (steps < max_steps) altitude_history[steps] = telemetry.altitude;
        steps++;
    }

    // print results
    printf("--- Rocket Telemetry ---\n");
    printf("Steps: %d Total time: %.1f s\n", steps, steps * dt);
    printf("Max altitude: %.1f m\n", max_altitude);
    printf("Final altitude: %.1f m\n", telemetry.altitude);
    printf("Final velocity: %.1f m/s\n", telemetry.velocity);
    printf("Fuel remaining: %.1f\n", sensor.fuel);
    printf("Altitude history (every 10 steps): ");
    // for (int i = 0; i <= steps; i += 10) {
    //     printf("%.2f, ", altitude_history[i]);
    // }

    return 0;
}