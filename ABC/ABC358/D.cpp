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
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    SORT(A);
    multiset<int> st;
    for (int i = 0; i < N; i++)
    {
        st.insert(A[i]);
    }
    int ans = 0;
    bool ok = true;
    for (int i = 0; i < M; i++)
    {
        auto itr = st.lower_bound(B[i]);
        if (itr == st.end())
        {
            ok = false;
            break;
        }
        st.erase(itr);
        ans += *itr;
    }
    if (ok)
    {
        cout << ans << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}
