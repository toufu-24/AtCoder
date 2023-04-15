#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int Alice = 0, Bob = 0;
    int N, num[100];

    //入力
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num[i]);
    }

    //バブルソート
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (num[j] < num[j + 1])
            {
                swap(&num[j], &num[j + 1]);
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (i % 2 == 0)
            Alice += num[i];
        else
            Bob += num[i];
    }

    printf("%d", Alice - Bob);
    return 0;
}