#include <bits/stdc++.h>
using namespace std;

int main()
{
    int Y;
    cin >> Y;
    while (1)
    {
        if (Y % 4 == 2)
        {
            break;
        }
        Y++;
    }
    cout << Y << endl;
}