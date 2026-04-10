#include<stdio.h>
#include "stack.h"

void init(Stack* s)
{
    s->top = -1;
}

void push(Stack* s, int value)
{
        if (is_full(s)) {
                printf("Stack overflow\n");
                return;
        }
        s->items[++(s->top)] = value;
}

int pop(Stack* s)
{
        if (is_empty(s)) {
                printf("Stack underflow\n");
                return -1; 
        }
        return s->items[(s->top)--];
}

bool is_full(Stack* s)
{
        return s->top == MAX_SIZE - 1;
}
bool is_empty(Stack* s)
{
        return s->top == -1;
}