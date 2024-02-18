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
    int a, N;
    cin >> a >> N;
    queue<pair<int, int>> q;
    q.push({1, 0});
    set<int> st;
    st.insert(1);
    while (!q.empty())
    {
        int now, cnt;
        tie(now, cnt) = q.front();
        q.pop();
        if (now == N)
        {
            cout << cnt << endl;
            return 0;
        }
        cnt++;
        if (now >= 10 && now % 10 != 0)
        {
            string S = to_string(now);
            string ori_S = S;
            char tmp = S[S.size() - 1];
            S.pop_back();
            S = tmp + S;
            int S_int = stoll(S);
            if (S_int <= N * 10 && !st.count(S_int))
            {
                q.push({S_int, cnt});
                st.insert(S_int);
            }
        }

        now *= a;

        if (now <= N * 10 && !st.count(now))
        {
            q.push({now, cnt});
            st.insert(now);
        }
    }
    cout << -1;
}
