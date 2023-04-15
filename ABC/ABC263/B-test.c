#include <stdio.h>
int P[50] = {};
int main(void)
{
    int N;
    int num = 1;
    int count = 1;
    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++)
    {
        scanf("%d", &P[i]);
    }

    for (int i = 0; num != P[N - 2]; i++)
    {
        if (P[i] == num)
        {
            num = i + 2;
            count++;
        }
    }

    printf("%d", count);

    return 0;
}