#include <stdio.h>

int main(void)
{
    int num[200];
    int N;
    int count = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num[i]);
    }

    while (1)
    {
        //偶数判定
        int flag = 0;
        for (int i = 0; i < N; i++)
        {
            if (num[i] % 2 != 0)
            {
                flag = 1;
            }
        }

        if (flag == 0)
        {
            for (int i = 0; i < N; i++)
            {
                num[i] /= 2;
            }
            count++;
        }
        else
            break;
    }
    printf("%d\n", count);
    return 0;
}