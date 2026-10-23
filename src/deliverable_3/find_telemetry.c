#include "include/sensor.h"
#include "include/find_telemetry.h"

// take a sensor sample and calculate velocity and altitude
void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry) {
    telemetry->sensor = *sensor;
    telemetry->velocity += sensor->acceleration * DT;        
    telemetry->altitude += telemetry->velocity * DT;

    // clamping altitude
    if (telemetry->altitude <= 0 && telemetry->velocity <= 0) {
        telemetry->altitude = 0;
    }
}