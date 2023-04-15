#include <stdio.h>
#include <string.h>

char Table[4][10] = {"eraser", "erase", "dreamer", "dream"};
char S[100000] = {};
char temp[100000] = {};

int main(void)
{
    scanf("%s", S);
    int flag;

    while (S[0] != '\0')
    {
        flag = 0;
        char part[4][8];
        strncpy(part[0], S, strlen(Table[0]));
        strncpy(part[1], S, strlen(Table[1]));
        strncpy(part[2], S, strlen(Table[2]));
        strncpy(part[3], S, strlen(Table[3]));

        part[0][strlen(Table[0])] = '\0';
        part[1][strlen(Table[1])] = '\0';
        part[2][strlen(Table[2])] = '\0';
        part[3][strlen(Table[3])] = '\0';

        int length = strlen(S);
        for (int i = 0; i < 4; i++)
        {
            if (strcmp(part[i], Table[0]) == 0 && S[strlen(Table[0]) + 1] != 'a' && S[strlen(Table[0]) + 2] != 's' && S[strlen(Table[0]) + 3] != 'e')
            {
                flag = 1;
                for (int i = 0; i < length - strlen(Table[0]); i++)
                {
                    temp[i] = S[i + strlen(Table[0])];
                }
                for (int i = 0; i < strlen(temp); i++)
                {
                    S[i] = temp[i];
                }
                for (int i = length - strlen(Table[0]); i < length; i++)
                    S[i] = '\0';
                break;
            }
            else if (strcmp(part[i], Table[1]) == 0)
            {
                flag = 1;
                for (int i = 0; i < length - strlen(Table[1]); i++)
                {
                    temp[i] = S[i + strlen(Table[1])];
                }
                for (int i = 0; i < strlen(temp); i++)
                {
                    S[i] = temp[i];
                }
                for (int i = length - strlen(Table[1]); i < length; i++)
                    S[i] = '\0';
                break;
            }
            else if (strcmp(part[i], Table[2]) == 0 && (S[strlen(Table[2]) + 1] != 'a' && S[strlen(Table[2]) + 2] != 's' && S[strlen(Table[2]) + 3] != 'e'))
            {
                flag = 1;
                for (int i = 0; i < length - strlen(Table[2]); i++)
                {
                    temp[i] = S[i + strlen(Table[2])];
                }
                for (int i = 0; i < strlen(temp); i++)
                {
                    S[i] = temp[i];
                }
                for (int i = length - strlen(Table[2]); i < length; i++)
                    S[i] = '\0';
                break;
            }
            else if (strcmp(part[i], Table[3]) == 0)
            {
                flag = 1;
                for (int i = 0; i < length - strlen(Table[3]); i++)
                {
                    temp[i] = S[i + strlen(Table[3])];
                }
                for (int i = 0; i < strlen(temp); i++)
                {
                    S[i] = temp[i];
                }
                for (int i = length - strlen(Table[3]); i < length; i++)
                    S[i] = '\0';
                break;
            }
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