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
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    int ans = 1e18;
    for (int i = 0; i < N; i++)
    {
        set<int> st;
        for (int j = 0; j < K; j++)
        {
            st.insert(P[i] + j);
        }
        int ini = 0;
        for (int j = 0; j < N; j++)
        {
            if (st.contains(P[j]))
            {
                if (st.size() == K)
                {
                    ini = j;
                }
                st.erase(P[j]);
                if (st.empty())
                {
                    ans = min(ans, j - ini);
                    break;
                }
            }
        }
    }

    cout << ans << endl;
}
