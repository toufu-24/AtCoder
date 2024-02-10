#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int Y;
    cin >> Y;
    int judge = Y % 4;
    switch (judge)
    {
    case 0:
        cout << Y + 2;
        break;
    case 1:
        cout << Y + 1;
        break;
    case 2:
        cout << Y;
        break;
    case 3:
        cout << Y + 3;
        break;
    default:
        break;
    }
}