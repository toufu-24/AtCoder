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
    ll N, A, B;
    cin >> N >> A >> B;
    ll A_cnt = N / A;
    ll A_sum = A_cnt * (2 * A + (A_cnt - 1) * A) / 2;
    ll B_cnt = N / B;
    ll B_sum = B_cnt * (2 * B + (B_cnt - 1) * B) / 2;
    ll AB_cnt = N / (lcm(A, B));
    ll AB_sum = AB_cnt * (2 * lcm(A, B) + (AB_cnt - 1) * lcm(A, B)) / 2;
    ll N_sum = N * (N + 1) / 2;
    cout << N_sum - A_sum - B_sum + AB_sum << endl;
}