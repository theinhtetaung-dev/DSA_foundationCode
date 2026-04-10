#include <stdio.h>
#include <assert.h>
#include "C:\Users\DELL\Desktop\DSA\TDD\StackTDD\Src\stack.h"
#include "C:\Users\DELL\Desktop\DSA\TDD\StackTDD\Src\stack.c"

Stack s;

void test_init()
{
        init(&s);
        assert(s.top == -1);
        printf("test_init passed\n");
}

void test_push()
{
        init(&s);
        push(&s, 10);
        assert(s.top == 0);
        assert(s.items[s.top] == 10);
        printf("test_push passed\n");
}

int main()
{
        test_init();
        test_push();
        return 0;
}