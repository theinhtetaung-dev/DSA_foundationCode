#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    int *items;
    int front, rear, size, capacity;
} Queue;

Queue* create_queue(int capacity);
int is_empty(Queue* q);
#endif