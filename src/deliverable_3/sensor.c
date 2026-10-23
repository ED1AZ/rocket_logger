#include "include/sensor.h"
#include "include/flight_config.h"

void update_sensor_sample(sensor_sample_s *sensor) {
     // increment timestamp
    sensor->timestamp += DT;

    // acceleration is dependent on fuel amount
    if (sensor->fuel > 0) { 
        sensor->acceleration = A_THRUST - G;
        sensor->fuel -= 1; // fuel depleted each step
    } else sensor->acceleration = -G;
}