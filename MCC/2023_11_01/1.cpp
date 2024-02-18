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
    int A, B, C;
    cin >> A >> B >> C;

    for (int i = 1; i <= B * (A + 100); i++)
    {
        if ((A * i) % B == C)
        {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
}