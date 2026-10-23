#pragma once
#include <stdint.h>

typedef struct {
    uint8_t * const buffer; // pointer to buffer storage 
    size_t head;  // write
    size_t tail;  // read
    size_t max;   
    size_t element_size; // for memcpy
} ring_buffer;

// used by find_telemetry
void push_discard_newest(ring_buffer *rb, const void *data);
// used by sensor update
void push_overwrite_oldest(ring_buffer *rb, const void *data);

void pop(ring_buffer *rb, void *out);