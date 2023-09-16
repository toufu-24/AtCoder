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
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;
    vector<ll> T(M), W(M), S(M);
    for (int i = 0; i < M; i++)
    {
        cin >> T[i] >> W[i] >> S[i];
    }
    vector<ll> somen(N, 0);
    vector<ll> back(N, 0);
    for (int i = 0; i < M; i++)
    {
        int eater = -1;
        for (int j = 0; j < N; j++)
        {
            if (back[j] <= T[i])
            {
                eater = j;
                somen[eater] += W[i];
                back[eater] = T[i] + S[i];
                break;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        cout << somen[i] << '\n';
    }
}