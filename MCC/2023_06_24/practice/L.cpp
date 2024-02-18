#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        string S;
        cin >> S;
        if (S == "#")
        {
            break;
        }
        string S2;
        cin >> S2;
        if (S < S2)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}