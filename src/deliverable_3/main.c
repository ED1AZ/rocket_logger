#include <stdint.h>
#include "include/main.h"
#include "include/flight_config.h"
#include "include/timer.h"
#include "include/sensor.h"
#include "include/find_telemetry.h"
#include "include/print_telemetry.h"
#include "include/state.h"

static task_s tasks[] = {
    { sample_sensor_task,   SENSOR_INTERVAL,    0 },
    { find_telemetry_task,  TELEMETRY_INTERVAL, 0 },
    { print_telemetry_task, PRINT_INTERVAL,     0 },
    { run_state_task,       STATE_INTERVAL,     0 },
};

#define NUM_TASKS (sizeof(tasks) / sizeof(tasks[0]))

void run_scheduler() {
    uint32_t now = get_ms();

    for (size_t i = 0; i < NUM_TASKS; i++) {
        if ((uint32_t)(now - tasks[i].last_ms) >= tasks[i].interval_ms) {
            tasks[i].last_ms = now;
            tasks[i].run();
        }
    }
}

int main(void){
    sample_sensor_init_rb();
    telemetry_init_rb();

    // access rocket landing
    while (!rocket_has_landed()) {
        run_scheduler();
    }

    uint32_t end = get_ms() + PRINT_INTERVAL;
    while ((int32_t)(get_ms() - end) < 0) {
        run_scheduler();
    }

    return 0;
}