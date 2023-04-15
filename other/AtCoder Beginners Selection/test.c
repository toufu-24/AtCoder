#include <stdio.h>
#include <string.h>

char Table[4][8] = {"dreamer", "dream", "eraser", "erase"};

int main(void)
{
    char str[100] = "abcd";
    int a = strlen("abcd");
    int b = strlen(str);
    printf("%d %d", a, b);
}