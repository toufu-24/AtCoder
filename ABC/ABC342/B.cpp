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
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    int Q;
    cin >> Q;
    while (Q--)
    {
        int a, b;
        cin >> a >> b;
        int a_idx = find(all(P), a) - P.begin();
        int b_idx = find(all(P), b) - P.begin();
        if (a_idx < b_idx)
        {
            cout << a << endl;
        }
        else
        {
            cout << b << endl;
        }
    }
}