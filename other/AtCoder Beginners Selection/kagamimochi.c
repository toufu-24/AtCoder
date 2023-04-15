#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int N, diameter[100];
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &diameter[i]);
    }

    //降順バブルソート
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (diameter[j] < diameter[j + 1])
            {
                swap(&diameter[j], &diameter[j + 1]);
            }
        }
    }

    int count = 1;
    for (int i = 0; i < N - 1; i++)
    {
        if (diameter[i] > diameter[i + 1])
            count++;
    }
    printf("%d\n", count);

    return 0;
}