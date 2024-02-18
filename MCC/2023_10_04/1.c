#include <stdio.h>

int max = 0;
#define push(a) ((stack[sp++] = (a)))
#define pop() (stack[--sp])
int fib2(int n)
{
    int stack[100], sp = 0, r;
    max = max > sp ? max : sp;
L0:
    if (n <= 1)
    {
        r = 1;
    }
    else
    {
        push(0);
        push(n);
        max = max > sp ? max : sp;
        n--;
        goto L0;
    L1:
        push(r);
        push(1);
        push(n);
        max = max > sp ? max : sp;
        n -= 2;
        goto L0;
    L2:
        r += pop();
    }
    if (sp == 0)
        return r;
    n = pop();
    max = max > sp ? max : sp;
    if (pop() == 0)
        goto L1;
    else
        goto L2;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("fib = %d\n", fib2(n));
    printf("max = %d\n", max);
    return 0;
}