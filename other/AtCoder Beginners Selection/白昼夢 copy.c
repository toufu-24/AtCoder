#include <stdio.h>
#include <string.h>

char Table[4][10] = {"eraser", "erase", "dreamer", "dream"};
char S[100000] = {};
char temp[100000] = {};

void move(int a, int length)
{
    for (int i = 0; i < length - strlen(Table[a]); i++)
    {
        temp[i] = S[i + strlen(Table[a])];
    }
    for (int i = 0; i < strlen(temp); i++)
    {
        S[i] = temp[i];
    }
    for (int i = length - strlen(Table[a]); i < length; i++)
        S[i] = '\0';
}

int main(void)
{
    scanf("%s", S);
    int flag;

    while (S[0] != '\0')
    {
        flag = 0;
        //初めの数文字を抜き出す
        char part[5][11];
        for (int i = 0; i < 4; i++)
        {
            strncpy(part[i], S, strlen(Table[i]));
            part[i][strlen(Table[i])] = '\0';
        }
        strncpy(part[4], S, strlen("dreamerase"));
        part[4][strlen("dreamerase")] = '\0';

        int length = strlen(S);

        // eraser
        if (strcmp(part[0], Table[0]) == 0)
        {
            flag = 1;
            move(0, length);
        }
        // erase
        else if (strcmp(part[1], Table[1]) == 0)
        {
            flag = 1;
            move(1, length);
        }
        // dream eraseのときはdreamでとる
        else if (strcmp(part[4], "dreamerase") == 0)
        {
            flag = 1;
            move(3, length);
        }
        // dreamer
        else if (strcmp(part[2], Table[2]) == 0)
        {
            flag = 1;
            move(2, length);
        }
        // dream
        else if (strcmp(part[3], Table[3]) == 0)
        {
            flag = 1;
            move(3, length);
        }

        if (flag != 1)
            break;
    }

    if (flag == 1)
        printf("YES\n");
    else if (flag == 0)
        printf("NO\n");

    return 0;
}