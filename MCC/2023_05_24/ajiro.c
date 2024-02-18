#include <stdio.h>

void calc_sum(int sum[], int a[], int b[])
{
    for (int i = 0; i < 3; i++)
    {
        sum[i] = a[i] + b[i];
    }
}

void calc_difference(int difference[], int a[], int b[])
{
    for (int i = 0; i < 3; i++)
    {
        difference[i] = a[i] - b[i];
    }
}

int main(void)
{
    int a[3], b[3];
    printf("一つ目の配列を入力\n");
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("二つ目の配列を入力\n");
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &b[i]);
    }

    int sum[3], difference[3];
    // sumとdifferenceを計算
    calc_sum(sum, a, b);
    calc_difference(difference, a, b);

    // sumとdifferenceを出力
    printf("和:");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", sum[i]);
    }
    printf("\n");

    printf("差:");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", difference[i]);
    }
    printf("\n");

    return 0;
}