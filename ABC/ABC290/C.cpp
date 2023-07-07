#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> tmp(N);
    vector<int> A;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp[i];
        if (tmp[i] < K)
        {
            A.emplace_back(tmp[i]);
        }
    }
    sort(A);
    // 重複要素を削除
    A.erase(unique(all(A)), A.end());
    for (int i = 0; i < K; i++)
    {
        if (i >= A.size())
        {
            cout << i << endl;
            return 0;
        }
        if (A[i] != i)
        {
            cout << i << endl;
            return 0;
        }
    }
    cout << K << endl;
}