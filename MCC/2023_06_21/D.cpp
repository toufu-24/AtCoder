#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    while (1)
    {
        int n;
        cin >> n;
        if (n == 0)
        {
            break;
        }
        vector<int> b(n);
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
        }
        sort(b);
        reverse(b);
        ll ans = 0;
        while (1)
        {
            bool three_get = false;
            int cnt = 0;
            for (int i = 0; i < n; i++)
            {
                if (b[i] != 0)
                {
                    b[i]--;
                    cnt++;
                }
                if (cnt == 3)
                {
                    three_get = true;
                    ans++;
                    break;
                }
            }
            if (!three_get)
            {
                break;
            }
        }
        cout << ans << endl;
    }
}
