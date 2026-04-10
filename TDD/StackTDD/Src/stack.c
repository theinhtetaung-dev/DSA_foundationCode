#include<stdio.h>
#include "stack.h"

void init(Stack* s)
{
    s->top = -1;
}

void push(Stack* s, int value)
{
        s->items[++(s->top)] = value;
}