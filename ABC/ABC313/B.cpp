#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; i++)
    {
        int A, B;
        cin >> A >> B;
        G[B - 1].push_back(A - 1);
    }

    bool exist = false;
    int ans = -1;
    for (int i = 0; i < N; i++)
    {
        if (G[i].size() == 0)
        {
            if (exist)
            {
                cout << -1 << endl;
                return 0;
            }
            else
            {
                exist = true;
                ans = i + 1;
            }
        }
    }
    cout << ans << endl;
}