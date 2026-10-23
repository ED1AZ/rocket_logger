#include "include/sensor.h"
#include "include/flight_config.h"
#include "include/buffer.h"

// define buffer and the storage for it based off sensor data type
static sensor_sample_s storage[SENSOR_BUFFER_SIZE];
static ring_buffer sensor_buffer;

static sensor_sample_s sensor = {0.0, INITIAL_FUEL, 0.0};

void update_sensor_sample(sensor_sample_s *sensor) {
     // increment timestamp
    sensor->timestamp += DT;

    // acceleration is dependent on fuel amount
    if (sensor->fuel > 0) { 
        sensor->acceleration = A_THRUST - G;
        sensor->fuel -= 1; // fuel depleted each step
    } else sensor->acceleration = -G;
}

void sample_sensor_init_rb() {
    rb_init(&sensor_buffer, storage, sizeof(sensor_sample_s), SENSOR_BUFFER_SIZE);
}

// makes sensor buffer visible to telemetry function
ring_buffer *get_sensor_buffer() {
    return &sensor_buffer;
}

void sample_sensor_task() {
    printf("Sample sensor task");
    update_sensor_sample(&sensor);
    push_overwrite_oldest(&sensor_buffer, &sensor);
}