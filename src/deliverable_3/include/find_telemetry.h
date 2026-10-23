#pragma once
#include "include/sensor.h"

typedef struct {
    sensor_sample_s sensor;
    double velocity;
    double altitude;
} telemetry_packet_s;

void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry);

// initialize telemetry buffer and task
ring_buffer *get_sensor_buffer();
void telemetry_init_rb();
void find_telemetry_task();
