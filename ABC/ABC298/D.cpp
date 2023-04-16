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
    int Q;
    cin >> Q;
    string S = "1";
    for (int i = 0; i < Q; i++)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            char x;
            cin >> x;
            S += x;
        }
        else if (q == 2)
        {
            string tmp;
            tmp.copy(const_cast<char *>(S.c_str() + 1), S.size() - 1);
            S = tmp;
        }
        else if (q == 3)
        {
            modint ans = 0;
            ll faster = 0;
            for (int j = 0; j < S.size(); j++)
            {
                faster += static_cast<long long>(S[j] - '0') * static_cast<long long>(pow(10, S.size() - j - 1));
                if (faster >= 10000000)
                {
                    ans += faster;
                    faster = 0;
                }
            }
            ans += faster;
            cout << ans.val() << "\n";
        }
    }
}