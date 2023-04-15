#include <stdio.h>

int main(void)
{
    int A, B, C, X;
    int count = 0;

    scanf("%d", &A);
    scanf("%d", &B);
    scanf("%d", &C);
    scanf("%d", &X);

    for (int i = 0; i <= A; i++)
    {
        for (int j = 0; j <= B; j++)
        {
            for (int k = 0; k <= C; k++)
            {
                if ((i * 500) + (j * 100) + (k * 50) == X)
                {
                    count++;
                }
            }
        }
    }
    printf("%d", count);
    return 0;
}