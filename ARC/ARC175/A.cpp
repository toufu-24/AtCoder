#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

using mint = modint998244353;

int32_t main()
{
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
        P[i]--;
    }
    string S;
    cin >> S;
    mint ans = 0;
    set<int> used_spoon;
    // 取られてないスプーンが連続 && そこに人がいない -> アウト
    vector<vector<int>> dp(N, vector<int>(2, 0));
    for (int i = 0; i < N; i++)
    {
        int human = P[i];
    }
}