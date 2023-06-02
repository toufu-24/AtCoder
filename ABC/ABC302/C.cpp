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
        cin >> S[i];
    sort(S);
    do
    {
        bool ok = true;
        for (int i = 0; i < N - 1; i++)
        {
            int cnt = 0;
            for (int j = 0; j < M; j++)
            {
                if (S[i][j] != S[i + 1][j])
                    cnt++;
                if (cnt >= 2)
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
                break;
        }
        if (ok)
        {
            cout << "Yes";
            return 0;
        }
    } while (next_permutation(S.begin(), S.end()));
    cout << "No";
}