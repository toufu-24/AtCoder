#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    while (true)
    {
        string s = to_string(N);
        if ((s[0] - '0') * (s[1] - '0') == (s[2] - '0'))
        {
            cout << N << endl;
            return 0;
        }
        N++;
    }
}