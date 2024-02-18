#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int ans = 1e18;
    // bitが立ってるとこで区切る
    int bit = (1 << (N - 1));
    for (int i = 0; i < bit; i++)
    {
        // cerr << bitset<32>(i) << endl;
        int xor_num = -1e9;
        int now = 0;
        bool xored = false;
        for (int j = 0; j < N; j++)
        {
            if (i & (1 << (j - 1)))
            {
                // cerr << bitset<4>(now) << endl;
                if (xor_num == -1e9)
                {
                    xor_num = now;
                }
                else
                {
                    xor_num ^= now;
                }
                now = A[j];
                // cerr << endl
                //  << A[j] << " ";
                xored = true;
            }
            else
            {
                // cerr << A[j] << " ";
                now |= A[j];
                xored = false;
            }
        }
        // cerr << bitset<4>(now) << endl;
        if (xor_num == -1e9)
        {
            xor_num = now;
        }
        else
        {
            xor_num ^= now;
        }

        ans = min(ans, xor_num);
        // cerr << "--------------" << endl;
    }
    cout << ans << endl;
}