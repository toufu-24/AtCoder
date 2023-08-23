#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    vector<vector<int>> modK(K);
    for (int i = 0; i < N; i++)
    {
        modK[i % K].push_back(a[i]);
    }
    for (int i = 0; i < K; i++)
    {
        sort(modK[i]);
    }
    vector<int> ans(N);
    for (int i = 0; i < K; i++)
    {
        int size = modK[i].size();
        for (int j = 0; j < size; j++)
        {
            ans[i + j * K] = modK[i][j];
        }
    }
    for (int i = 0; i < N - 1; i++)
    {
        if (ans[i] > ans[i + 1])
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}