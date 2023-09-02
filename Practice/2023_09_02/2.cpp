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
    int N;
    cin >> N;
    vector<int> X(N);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i];
    }
    int ave1 = accumulate(all(X), 0) / N;
    int ave2 = accumulate(all(X), 0) / N + 1;
    int ans1 = 0;
    int ans2 = 0;
    for (int i = 0; i < N; i++)
    {
        ans1 += (X[i] - ave1) * (X[i] - ave1);
        ans2 += (X[i] - ave2) * (X[i] - ave2);
    }
    cout << min(ans1, ans2);
}