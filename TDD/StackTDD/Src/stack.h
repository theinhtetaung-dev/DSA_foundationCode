#ifndef STSCK_H
#define STSCK_H
#include <stdbool.h>
#define MAX_SIZE 100

typedef struct 
{
        int items[MAX_SIZE];
        int top;
}Stack;

void init(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
bool is_empty(Stack *s);
bool is_full(Stack *s); 
#endif