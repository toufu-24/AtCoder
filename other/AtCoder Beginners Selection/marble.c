#include <stdio.h>
#define num 3

int main(void)
{
    char a[3];
    int count = 0;
    scanf("%s", a);

    for (int i = 0; i < num; i++)
    {
        if (a[i] == '1')
        {
            count++;
        }
    }
    printf("%d", count);
    return 0;
}