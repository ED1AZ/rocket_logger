#pragma once
#include <stdint.h>
#include "buffer.h"

typedef struct {
    double acceleration;
    uint16_t fuel;
    float timestamp;
} sensor_sample_s;

void update_sensor_sample(sensor_sample_s *sensor);

// initialize sample sensor buffer and task
ring_buffer *get_sensor_buffer();
void sample_sensor_init_rb();
void sample_sensor_task();
