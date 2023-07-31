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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    // 左側から見た時の最大値
    vector<int> left(N);
    left[0] = A[0];
    for (int i = 1; i < N; i++)
    {
        left[i] = max(left[i - 1], A[i]);
    }
    // 右側から見た時の最大値
    vector<int> right(N);
    right[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        right[i] = max(right[i + 1], A[i]);
    }
    int D;
    cin >> D;
    vector<pair<int, int>> room(D);
    for (int i = 0; i < D; i++)
    {
        cin >> room[i].first >> room[i].second;
        cout << max(left[room[i].first - 2], right[room[i].second]) << endl;
    }
}