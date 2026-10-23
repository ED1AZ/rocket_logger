#pragma once
#include <stdint.h>

typedef struct {
    double acceleration;
    uint16_t fuel;
    float timestamp;
} sensor_sample_s;

void update_sensor_sample(sensor_sample_s *sensor);