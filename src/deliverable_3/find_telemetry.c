#include "include/sensor.h"
#include "include/find_telemetry.h"
#include "include/flight_config.h"

static ring_buffer telemetry_buffer;
static telemetry_packet_s storage[TELEMETRY_BUFFER_SIZE];
static telemetry_packet_s telemetry = {{0.0, INITIAL_FUEL, 0.0}, INITIAL_VELOCITY, INITIAL_ALTITUDE};

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

void telemetry_init_rb() {
    rb_init(&telemetry_buffer, storage, sizeof(telemetry_packet_s), TELEMETRY_BUFFER_SIZE);
}