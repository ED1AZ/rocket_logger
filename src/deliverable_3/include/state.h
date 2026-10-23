#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "find_telemetry.h"

typedef enum {
    FLIGHT_PRELAUNCH,
    FLIGHT_ASCENT,
    FLIGHT_COAST,
    FLIGHT_DESCENT,
    FLIGHT_LANDED
} rocket_state;

void run_rocket_state(const telemetry_packet_s *telemetry);
void run_state_task(void);
bool rocket_has_landed(void);