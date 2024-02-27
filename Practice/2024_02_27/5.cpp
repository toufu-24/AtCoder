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
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }

    // ある段階でK番より後ならそれ以降で出てくるわけないよね
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < K; i++)
    {
        pq.push(P[i]);
    }
    cout << pq.top() << endl;
    for (int i = K; i < N; i++)
    {
        pq.push(P[i]);
        pq.pop();
        cout << pq.top() << endl;
    }
}