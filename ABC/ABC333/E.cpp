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
    int K_min = 1e9;
    string ans;
    vector<int> t(N);
    vector<int> x(N);
    for (int i = 0; i < N; i++)
    {
        cin >> t[i] >> x[i];
    }

    multiset<int> enemys;
    for (int i = N - 1; i >= 0; i--)
    {
        switch (t[i])
        {
        case 1:
            if (enemys.find(x[i]) != enemys.end())
            {
                ans += "1";
                enemys.erase(enemys.find(x[i]));
            }
            else
            {
                ans += "0";
            }
            break;
        case 2:
            enemys.insert(x[i]);
            break;
        default:
            break;
        }
    }

    if (enemys.size() == 0)
    {
        // 倒しきれる場合
        REVERSE(ans);
        int K = 0;
        int K_max = 0;
        int ans_cnt = 0;
        for (int i = 0; i < N; i++)
        {
            if (t[i] == 1)
            {
                if (ans[ans_cnt] == '1')
                {
                    K++;
                    K_max = max(K_max, K);
                }
                ans_cnt++;
            }
            else
            {
                K = max(K - 1, 0);
            }
        }
        cout << K_max << endl;
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
    }
    else
    {
        cout << -1 << endl;
    }
}