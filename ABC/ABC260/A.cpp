#include <bits/stdc++.h>
using namespace std;
const int num = 3;

int main()
{
    string S;
    cin >> S;
    int i, flag = 0;
    for (i = 0; i < num; i++)
    {
        flag = 0;
        for (int j = 0; j < num; j++)
        {
            if (i != j)
                if (S.at(i) == S.at(j))
                {
                    flag = 1;
                    break;
                }
        }
        if (flag == 0)
            break;
    }
    if (flag == 1)
        cout << "-1" << endl;
    else
        cout << S.at(i) << endl;
}