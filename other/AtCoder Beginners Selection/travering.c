#include <stdio.h>

int t[100000], x[100000], y[100000];

int judge(int i, int N)
{
    int x_difference, y_difference;
    if (x[i] < x[i + 1])
        x_difference = x[i + 1] - x[i];
    else if (x[i] >= x[i + 1])
        x_difference = x[i] - x[i + 1];
    if (y[i] < y[i + 1])
        y_difference = y[i + 1] - y[i];
    else if (y[i] >= y[i + 1])
        y_difference = y[i] - y[i + 1];

    int t_difference = t[i + 1] - t[i];
    int extra_time = t_difference - x_difference - y_difference;
    if (extra_time % 2 == 0 && extra_time > 0)
        t_difference -= extra_time;

    if (x_difference + y_difference - t_difference == 0)
        return 0;
    else
        return 1;
}

int main(void)
{
    int N;
    scanf("%d", &N);
    t[0] = 0;
    x[0] = 0;
    y[0] = 0;
    for (int i = 1; i <= N; i++)
        scanf("%d%d%d", &t[i], &x[i], &y[i]);

    int tmp = 0;
    for (int i = 0; i < N; i++)
    {
        tmp = judge(i, N);
        if (tmp == 1)
            break;
    }
    if (tmp == 0)
        printf("Yes");
    else if (tmp == 1)
        printf("No");
    return 0;
}