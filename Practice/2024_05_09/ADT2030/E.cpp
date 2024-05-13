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
    int N;
    cin >> N;
    vector<string> S(N);
    int ans = 0;
    set<string> st;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        string rev = S[i];
        REVERSE(rev);
        if (st.contains(S[i]) || st.contains(rev))
        {
            continue;
        }
        else
        {
            ans++;
            st.insert(S[i]);
            if (st.contains(rev))
            {
                continue;
            }
            else
            {
                st.insert(rev);
            }
        }
    }
    cout << ans << endl;
}
