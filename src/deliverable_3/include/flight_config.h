#pragma once

// flight constants
#define G 9.81
#define INITIAL_ALTITUDE 0.0
#define INITIAL_VELOCITY 0.0
#define INITIAL_FUEL 50
#define A_THRUST 15
#define DT 0.1
#define MAX_STEPS 300

// buffer stuff
#define SENSOR_BUFFER_SIZE 16
#define TELEMETRY_BUFFER_SIZE 16

// task scheduling intervals, in ms
// frequenchy Hz = 1000/ms
#define SENSOR_INTERVAL 100 // 0.1 s
#define TELEMETRY_INTERVAL 400
#define PRINT_INTERVAL 800
#define STATE_INTERVAL 200