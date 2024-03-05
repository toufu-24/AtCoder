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
    vector<string> S(2);
    cin >> S[0] >> S[1];
    vector<vector<string>> ng = {
        {".#", "#."},
        {"#.", ".#"}};
    for (int i = 0; i < 2; i++)
    {
        if (S == ng[i])
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
}