#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ll K;
    cin >> K;
    // 2進数変換
    string s = "";
    while (K > 0)
    {
        s += to_string(K % 2 * 2);
        K /= 2;
    }
    REVERSE(s);
    cout << s;
}