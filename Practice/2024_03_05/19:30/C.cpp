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
    vector<string> v;
    for (int i = 0; i < S.size() * 2; i++)
    {
        v.push_back(S);
        S = S[S.size() - 1] + S.substr(0, S.size() - 1);
    }
    SORT(v);
    cout << v[0] << endl;
    cout << v[v.size() - 1] << endl;
}