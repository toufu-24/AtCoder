#include <stdio.h>
#include <stdlib.h>

int compare_int(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
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
    qsort(num, N, sizeof(int), compare_int);

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