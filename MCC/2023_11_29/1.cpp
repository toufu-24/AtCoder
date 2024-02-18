#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    priority_queue<int, vector<int>, greater<int>> Q;
    for (int i = 0; i < K; i++)
    {
        Q.push(P[i]);
    }
    cout << Q.top() << endl;
    for (int i = K; i < N; i++)
    {
        if (P[i] > Q.top())
        {
            Q.pop();
            Q.push(P[i]);
        }
        cout << Q.top() << endl;
    }
}