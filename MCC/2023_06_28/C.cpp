#include <bits/stdc++.h>
using namespace std;

#define ll int64_t

int main()
{
    for (ll n = 1; n * (n + 1) * (n + 2) / 6 < 10e6; n++)
    {
        if (n * (n + 1) * (n + 2) / 6 % 2 == 1)
            cout << n * (n + 1) * (n + 2) / 6 << ",";
    }
}