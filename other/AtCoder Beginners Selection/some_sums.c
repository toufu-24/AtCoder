#include <stdio.h>
#include <string.h>

int num[10000];

int main(void)
{
    int N, min, max;
    int k = 0, number = 0;
    scanf("%d%d%d", &N, &min, &max);

    for (int i = 1; i <= N; i++)
    {
        char tmp[6];
        for (int j = 0; j < 5; j++)
        {
            tmp[j] = '0';
        }
        sprintf(tmp, "%d", i);
        int length = strlen(tmp);
        tmp[length] = '0';
        tmp[6] = '\0';

        int i_num[5];
        for (int j = 0; j < 5; j++)
        {
            i_num[j] = tmp[j] - '0';
        }

        int judge = i_num[0] + i_num[1] + i_num[2] + i_num[3] + i_num[4];
        if (min <= judge && judge <= max)
        {
            num[k] = i;
            k++;
        }
    }

    for (int i = 0; i < k; i++)
    {
        number += num[i];
    }

    printf("%d\n", number);
    return 0;
}