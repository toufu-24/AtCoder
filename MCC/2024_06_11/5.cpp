#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

map<int, string> memo;
string burger(int N)
{
    if (N == 0)
    {
        return "P";
    }
    if (memo.count(N))
    {
        return memo[N];
    }
    string s = burger(N - 1);
    return memo[N] = "B" + s + "P" + s + "B";
}

int patty(int N, int X)
{
    if (N == 0)
    {
        if (X <= 1)
        {
            return 0;
        }
        return 1;
    }
    if (X <= 1 + burger(N - 1).size())
    {
        return patty(N - 1, X - 1);
    }
    return patty(N - 1, X - 2 - burger(N - 1).size()) + 1 + patty(N - 1, X - 2 - burger(N - 1).size());
}

int32_t main()
{
    int N, X;
    cin >> N >> X;
    vector<int> size(N + 1);
    vector<int> patt
    for (int i = 0; i < N; i++)
    {
        size[i] = burger(i).size();
    }
    
    auto tmp = patty(N, X);
    cout << tmp << endl;
}
