#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll
int32_t main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> ok, ng;
    for (int i = 0; i < M; i++)
    {
        int c;
        cin >> c;
        vector<int> v(c);
        for (int j = 0; j < c; j++)
        {
            cin >> v[j];
        }
        char result;
        cin >> result;
        if (result == 'o')
        {
            ok.push_back(v);
        }
        else
        {
            ng.push_back(v);
        }
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << N); mask++)
    {
        bool valid = true;
        for (const auto &test : ok)
        {
            int count = 0;
            for (int key : test)
            {
                if (mask & (1 << (key - 1)))
                {
                    count++;
                }
            }
            if (count < K)
            {
                valid = false;
                break;
            }
        }
        if (!valid)
            continue;
        for (const auto &test : ng)
        {
            int count = 0;
            for (int key : test)
            {
                if (mask & (1 << (key - 1)))
                {
                    count++;
                }
            }
            if (count >= K)
            {
                valid = false;
                break;
            }
        }
        if (valid)
        {
            ans++;
        }
    }
    cout << ans << endl;
}
