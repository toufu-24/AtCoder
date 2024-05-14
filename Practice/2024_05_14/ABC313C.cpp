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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);
    int sum = reduce(all(A));
    int ave = sum / N;
    int rem = sum % N;
    vector<int> goal(N, sum / N);
    for (int i = 0; i < sum % N; i++)
    {
        goal[N - i - 1]++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans += abs(A[i] - goal[i]);
    }
    cout << ans / 2 << endl;
}
