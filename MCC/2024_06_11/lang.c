#include <stdio.h>

int main()
{
    int x = 1;
    printf("%d\n", x == (0 ? 1 : x == 1 ? 2
                                        : 3));
    printf("%d\n", x == 0 ? 1 : x == 1 ? 2
                                       : 3);
}