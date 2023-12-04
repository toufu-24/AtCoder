#include <stdio.h>

/**
 * Calculates the nth Fibonacci number recursively.
 * 
 * @param n The index of the Fibonacci number to calculate.
 * @return The nth Fibonacci number.
 */
int fib(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return fib(n - 2) + fib(n - 1);
    }
}

int main()
{
}