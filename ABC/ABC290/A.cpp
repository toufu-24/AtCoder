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
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (auto &x : A)
        cin >> x;
    vector<int> B(M);
    for (auto &x : B)
        cin >> x;

    int ans = 0;
    for (int i = 0; i < M; i++)
    {
        ans += A[B[i] - 1];
    }
    cout << ans << endl;
}