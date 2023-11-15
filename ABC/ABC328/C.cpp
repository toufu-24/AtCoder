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
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    vector<int> sum(N, 0);
    for (int i = 1; i < N; i++)
    {
        sum[i] = sum[i - 1] + (S[i] == S[i - 1] ? 1 : 0);
    }
    for (int q = 0; q < Q; q++)
    {
        int l, r;
        cin >> l >> r;
        cout << sum[r - 1] - sum[l - 1] << endl;
    }
}