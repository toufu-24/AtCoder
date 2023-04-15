#include <stdio.h>

int main(void)
{
    int N, Y;
    int flag = 0;
    int correct[3];
    scanf("%d%d", &N, &Y);

    for (int i = 0; i <= (2 * 10000000) / 1000; i++)
    {
        for (int j = 0; j <= (2 * 10000000) / 5000 - i; j++)
        {
            for (int k = 2000; k <= (2 * 10000000) / 10000 - i - j; k--)
            {
                if ((i * 1000) + (j * 5000) + (k * 10000) == Y && i + j + k == N)
                {
                    flag = 1;
                    correct[0] = i;
                    correct[1] = j;
                    correct[2] = k;
                    break;
                }
            }
            if ((i * 1000) + (j * 5000) > Y)
                break;
            if (flag == 1)
                break;
        }
        if (flag == 1)
            break;
    }

    if (flag == 1)
        printf("%d %d %d", correct[2], correct[1], correct[0]);
    else
        printf("-1 -1 -1");

    return 0;
}