#include <assert.h>
#include <stdio.h>
#include "C:\Users\DELL\Desktop\DSA\TDD\QueueTDD\Src\queue.h"

void test_create_queue() {
    Queue* q = create_queue(5);
    assert(is_empty(q) == 1); 
    printf("Test Create Queue: Passed\n");
}

int main() {
    test_create_queue();
    return 0;
}