#include <stdio.h>

int main(void)
{
    int L1, R1, L2, R2;
    scanf("%d%d%d%d", &L1, &R1, &L2, &R2);
    int length;
    if (L1 < L2)
    {
        if (R1 < R2)
            length = R1 - L2;
        else
            length = R2 - L2;
    }
    else if (R1 < R2)
        length = R1 - L1;
    else
        length = R2 - L1;

    if (length < 0)
        length = 0;

    printf("%d", length);
    return 0;
}