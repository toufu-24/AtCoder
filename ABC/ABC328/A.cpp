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
    int N, X;
    cin >> N >> X;
    vector<int> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    SORT(S);
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] > X)
        {
            break;
        }
        sum += S[i];
    }
    cout << sum << endl;
}