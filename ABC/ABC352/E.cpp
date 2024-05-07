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
    int N, M;
    cin >> N >> M;
    dsu d(N);
    vector<vector<int>> A(M);
    vector<pair<int, int>> C(M);
    for (int i = 0; i < M; i++)
    {
        int k, c;
        cin >> k >> c;
        A[i].resize(k);
        for (int j = 0; j < k; j++)
        {
            cin >> A[i][j];
            A[i][j]--;
        }
        C[i] = {c, i};
    }
    SORT(C);

    for (int i = 0; i < M; i++)
    {
        int c = C[i].first;
        int idx = C[i].second;
        // 全域木を作る
        
    }
}
