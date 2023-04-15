#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    vector<string> T(M);
    for (int i = 0; i < M; i++)
    {
        cin >> T[i];
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        string tmp = S[i].substr(S[i].length() - 3);
        for (int j = 0; j < M; j++)
        {
            if (tmp == T[j])
            {
                ans++;
                break;
            }
        }
    }
    cout << ans;
}