#include <stdio.h>
#include "include/state.h"

static rocket_state state = FLIGHT_PRELAUNCH;

void run_rocket_state(const telemetry_packet_s *telemetry) {
    switch (state) {
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
                printf("ascending\n");
            }
            break;
        case FLIGHT_ASCENT:
            if (telemetry->sensor.fuel <= 0 && telemetry->velocity > 0) {
                state = FLIGHT_COAST;
                printf("coasting\n");
            }
            break;
        case FLIGHT_COAST:
            if (telemetry->velocity <= 0) {
                state = FLIGHT_DESCENT;
                printf("descending\n");
            }
            break;
        case FLIGHT_DESCENT:
            if (telemetry->altitude <= 0) {
                state = FLIGHT_LANDED;
                printf("landed\n");
            }
            break;
        default:
            printf("Error: Invalid rocket state\n");
            break;
    }
}