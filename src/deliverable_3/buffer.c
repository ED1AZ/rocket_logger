#include <stdint.h>
#include "include/buffer.h"

// used by find_telemetry
void push_discard_newest(ring_buffer *rb, const void *data) {

}

// used by sensor update
void push_overwrite_oldest(ring_buffer *rb, const void *data) {

}

int pop(ring_buffer *rb, void *out) {
    int next;

    // check if empty
    if (rb->head == rb->tail) return -1;

    next = rb->tail + 1;

    // if next in tail reaches max, circle back to 0
    if (next >= rb->max) next = 0;

    // pop from buffer and read into output
    *out = rb->buffer[rb->tail];
    rb->tail = next;
    return 0;
}