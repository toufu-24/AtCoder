#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N, count = 0;
    int *P; //人2から
    scanf("%d", &N);
    int num = N;
    P = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N - 1; i++)
    {
        scanf("%d", &P[i]);
    }
    while (num != 1)
    {
        num = P[num - 2];
        count++;
    }

    printf("%d", count);

    return 0;
}