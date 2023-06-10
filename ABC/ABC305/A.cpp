#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    string N;
    cin >> N;
    if (N.size() == 1)
    {
        if (N[0] <= '2')
        {
            cout << 0;
        }
        else if ('3' <= N[0] && N[0] <= '7')
        {
            cout << 5;
        }
        else if (N[0] <= '8')
        {
            cout << 1;
            cout << 0;
        }
        return 0;
    }
    else if (N.size() == 2)
    {
        if (N[1] <= '2')
        {
            cout << N[0];
            cout << 0;
        }
        else if ('3' <= N[1] && N[1] <= '7')
        {
            cout << N[0];
            cout << 5;
        }
        else if (N[1] <= '8')
        {
            cout << int(N[0] - '0') + 1;
            cout << 0;
        }
    }
    else
    {
        cout << 100;
    }
}