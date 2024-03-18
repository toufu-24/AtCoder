#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, L;
    cin >> N >> L;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int plus = L - reduce(all(A));
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; i++)
    {
        pq.push(A[i]);
    }
    if (plus != 0)
        pq.push(plus);
    int ans = 0;
    while (pq.size() != 1)
    {
        int one = pq.top();
        pq.pop();
        int two = pq.top();
        pq.pop();
        ans += one + two;
        pq.push(one + two);
    }
    cout << ans << endl;
}