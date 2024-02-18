#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ull uint64_t

int main()
{
    ll N, M, K;
    cin >> N >> M >> K;
    vector<pair<ull, ull>> A(N, pair<ull, ull>(0, 0));
    for (int i = 0; i < N; i++)
    {
        cin >> A[i].second;
    }
    // 2進数変換
    vector<vector<int>> Binary(N, vector<int>(M));
    for (int i = 0; i < N; i++)
    {
        ull a = A[i].second;
        for (int j = 0; j < M; j++)
        {
            Binary[i][j] = a % 2;
            a /= 2;
        }
        for (int j = 0; j < Binary[i].size(); j++)
        {
            if (Binary[i][j] == 1)
                A[i].first++;
        }
    }
    sort(A);

    vector<ull> elite(K);
    for (int i = 0; i < K; i++)
    {
        elite[i] = A[i].second;
    }
}