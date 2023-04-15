#include <bits/stdc++.h>
using namespace std;

int main()
{
    string S;
    cin >> S;

    int p_count = 0, s_count = 0, sum = 1;

    for (int i = 0; i < S.size(); i++)
    {
        if (S.at(i) == '+')
            p_count++;
        else if (S.at(i) == '-')
            s_count++;
    }
    for (int i = 0; i < p_count; i++)
    {
        sum++;
    }
    for (int i = 0; i < s_count; i++)
    {
        sum--;
    }
    cout << sum << endl;
}
