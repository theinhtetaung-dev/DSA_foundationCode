#ifndef STSCK_H
#define STSCK_H
#define MAX_SIZE 100

typedef struct 
{
        int items[MAX_SIZE];
        int top;
}Stack;

void init(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);

#endif