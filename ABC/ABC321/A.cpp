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
    string S;
    cin >> S;
    char prev = S[0];
    for (int i = 1; i < S.size(); i++)
    {
        if (int(prev - '0') <= int(S[i] - '0'))
        {
            cout << "No" << endl;
            return 0;
        }
        prev = S[i];
    }
    cout << "Yes" << endl;
}