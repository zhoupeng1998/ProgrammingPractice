#include <stdio.h>

#include "calc.h"

int myadd(int a, int b)
{
    return a + b;
}

int mysub(int a, int b)
{
    return a - b;
}

int mymul(int a, int b)
{
    return a * b;
}

int mydiv(int a, int b)
{
    return a / b;
}

void printnum(int a)
{
    printf("Inside printnum, the number is %d\n", a);
}

void hiddenfunc()
{
    printf("You can't see me!\n");
}