#include <stdio.h>
char A[1000][1000];
int main(void)
{
    int flag = 0;
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%s", A[i]);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                if (A[i][j] != '-')
                {
                    flag = 1;
                    break;
                }
            }
            else if (A[i][j] == 'W' && A[j][i] != 'L')
            {
                flag = 1;
                break;
            }
            else if (A[i][j] == 'L' && A[j][i] != 'W')
            {
                flag = 1;
                break;
            }
            else if (A[i][j] == 'D' && A[j][i] != 'D')
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }

    if (flag == 0)
        printf("correct");
    else
        printf("incorrect");

    return 0;
}