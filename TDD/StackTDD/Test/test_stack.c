#include<stdio.h>
#include <assert.h>
#include "C:\Users\DELL\Desktop\DSA\TDD\StackTDD\Src\stack.h"

void test_init()
{
    Stack s;
    init(&s);
    assert(s.top == -1);
    printf("test_init passed\n");
}

int main()
{
    test_init();
    return 0;
}