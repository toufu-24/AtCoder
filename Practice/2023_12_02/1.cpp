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
    int N, A, B;
    cin >> N >> A >> B;
    int ans = A + B;
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }
    for (int i = 0; i < N; i++)
    {
        if (ans == C[i])
        {
            cout << i + 1;
            return 0;
        }
    }
}