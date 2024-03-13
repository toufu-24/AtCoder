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
    int N, M;
    cin >> N >> M;
    vector<string> s(N);
    for (int i = 0; i < N; i++)
    {
        cin >> s[i];
    }
    vector<string> t(M);
    for (int i = 0; i < M; i++)
    {
        cin >> t[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        bool flag = false;
        for (int j = 0; j < M; j++)
        {
            if (s[i].ends_with(t[j]))
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            ans++;
        }
    }
    cout << ans << endl;
}