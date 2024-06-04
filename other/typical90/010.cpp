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

int32_t main()
{
    int N;
    cin >> N;
    vector<int> C(N), P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i] >> P[i];
        C[i]--;
    }
    vector<vector<int>> sum(2, vector<int>(N + 1, 0));
    for (int i = 0; i < N; i++)
    {
        sum[0][i + 1] = sum[0][i];
        sum[1][i + 1] = sum[1][i];
        sum[C[i]][i + 1] += P[i];
    }
    int Q;
    cin >> Q;
    while (Q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        r++;
        cout << sum[0][r] - sum[0][l] << " ";
        cout << sum[1][r] - sum[1][l] << endl;
    }
}
