#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char s[200000][20];
int count[200000] = {};
int main(void)
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%s", s[i]);
    }
    system("clear");
    for (int i = 0; i < N; i++)
    {
        count[i] = 0;
        for (int j = 0; j < i; j++)
        {
            if (strcmp(s[i], s[j]) == 0)
            {
                count[i]++;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (count[i] > 0)
            printf("%s(%d)\n", s[i], count[i]);
        else
            printf("%s\n", s[i]);
    }
    return 0;
}