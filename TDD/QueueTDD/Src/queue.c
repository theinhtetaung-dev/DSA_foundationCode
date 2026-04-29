#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* create_queue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->rear = -1;
    q->items = (int*)malloc(capacity * sizeof(int));
    return q;
}

int is_empty(Queue* q) {
    return q->size == 0;
}