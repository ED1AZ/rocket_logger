#pragma once
#include <stdint.h>

typedef enum {
    FLIGHT_PRELAUNCH,
    FLIGHT_ASCENT,
    FLIGHT_COAST,
    FLIGHT_DESCENT,
    FLIGHT_LANDED
} rocket_state;

void run_rocket_state(const telemetry_packet_s *telemetry);