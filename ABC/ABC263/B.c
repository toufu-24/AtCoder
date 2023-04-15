#include <stdio.h>

int P[100]; //人2から

int main(void)
{
    int N;
    int num = 1, count = 1;
    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++)
    {
        scanf("%d", &P[i]);
    }

    while (1)
    {
        for (int i; i < N; i++)
        {
            if (P[i] == num)
            {
                num = i + 2;
                count++;
            }
        }
        if (num == P[N - 2])
        {
            break;
        }
        printf("a");
    }

    printf("%d", count);

    return 0;
}