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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<pair<int, int>> A_index;
    for (int i = 0; i < N; i++)
    {
        A_index.push_back({A[i], i});
    }
    SORT(A_index);
    vector<int> sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        sum[i + 1] = sum[i] + A_index[i].first;
    }
    vector<int> ans(N, 0);
    for (int i = 0; i < N; i++)
    {
        ans[A_index[i].second] = sum[N] - sum[i + 1];
    }
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << " ";
    }
}