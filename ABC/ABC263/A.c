#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int count[5];

int main(void)
{
    int card[5], flag = 0;
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &card[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (card[i] == card[j])
            {
                count[i]++;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (count[i] == 2 && count[i + 1] == 3)
        {
            flag = 1;
            break;
        }
        if (count[i] == 3 && count[i + 1] == 2)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        printf("Yes");
    }
    else
        printf("No");

    return 0;
}