#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<vector<char>> pin(7, vector<char>(2, '9'));
    vector<int> count(7, 0);
    for (int i = 1; i <= 10; i++)
    {
        if (i == 7)
        {
            cin >> pin[0][count[0]];
            count[0]++;
        }
        else if (i == 4)
        {
            cin >> pin[1][count[1]];
            count[1]++;
        }
        else if (i == 2 || i == 8)
        {
            cin >> pin[2][count[2]];
            count[2]++;
        }
        else if (i == 1 || i == 5)
        {
            cin >> pin[3][count[3]];
            count[3]++;
        }
        else if (i == 3 || i == 9)
        {
            cin >> pin[4][count[4]];
            count[4]++;
        }
        else if (i == 6)
        {
            cin >> pin[5][count[5]];
            count[5]++;
        }
        else if (i == 10)
        {
            cin >> pin[6][count[6]];
            count[6]++;
        }
    }
    if (pin[3][0] == '0')
    {
        bool answer = false;
        for (int i = 0; i < 5; i++)
        {
            //ピンが立ってるか
            bool flag1 = false;
            for (int j = 0; j < count[i]; j++)
            {
                if (pin[i][j] == '1')
                {
                    flag1 = true;
                    break;
                }
            }
            if (!flag1)
            {
                continue;
            }
            //次の列にピンが立っていないか
            bool flag2 = true;
            for (int j = 0; j < count[i + 1]; j++)
            {
                if (pin[i + 1][j] == '1')
                {
                    flag2 = false;
                    break;
                }
            }
            //次の次の列以降にピンが立ってるところはあるか
            if (flag2)
            {
                for (int j = i + 2; j < 7; j++)
                {
                    for (int k = 0; k < count[j]; k++)
                    {
                        if (pin[j][k] == '1')
                        {
                            answer = true;
                            break;
                        }
                    }
                    if (answer)
                    {
                        break;
                    }
                }
            }
            if (answer)
            {
                break;
            }
        }
        if (answer)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    else
    {
        cout << "No" << endl;
    }
}