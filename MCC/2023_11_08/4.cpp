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
using mint = modint;

signed main()
{
    int N, _X, M;
    cin >> N >> _X >> M;
    modint::set_mod(M);
    mint X = _X;
    vector<int> st;
    st.push_back(X.val());
    int ans = X.val();
    for (int i = 1; i < N; i++)
    {
        X *= X;
        if (binary_search(all(st), X.val()))
        {
            int idx = lower_bound(all(st), X.val()) - st.begin();
            int loop = st.size() - idx;
            int sum = 0;
            for (int j = idx; j < st.size(); j++)
            {
                sum += st[j];
            }
            int rest = (N - i) % loop;
            ans += sum * ((N - i) / loop) + sum;
            for (int j = idx; j < idx + rest; j++)
            {
                ans += st[j];
            }
            st.clear();
        }
        else
        {
            st.push_back(X.val());
            ans += X.val();
        }
    }
    cout << ans << endl;
}