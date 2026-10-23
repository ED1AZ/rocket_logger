#include "include/find_telemetry.h"
#include "include/buffer.h"

void print_telemetry_task() {
    ring_buffer *telemetry_buffer = get_telemetry_buffer();
    telemetry_packet_s p;
    printf("TELEMETRY PRINTING");

    // print telemetry values while popping 
    while (pop(telemetry_buffer, &p) == 0) {
        printf("t=%.1f s \n   velocity=%.1f m/s     altitude=%.1f m     fuel=%u\n",
        p.sensor.timestamp, p.velocity, p.altitude, p.sensor.fuel);
    }
}