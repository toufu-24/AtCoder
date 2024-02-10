#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort_(v) sort(v.begin(), v.end())
#define rsort_(v) sort(v.rbegin(), v.rend())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int X, Y, A, B, C;
    cin >> X >> Y >> A >> B >> C;
    vector<int> p(A), q(B), r(C);
    for (int i = 0; i < A; i++)
    {
        cin >> p[i];
    }
    rsort_(p);
    for (int i = 0; i < B; i++)
    {
        cin >> q[i];
    }
    rsort_(q);
    for (int i = 0; i < C; i++)
    {
        cin >> r[i];
    }
    rsort_(r);
    vector<int> good_p(X), good_q(Y);
    for (int i = 0; i < X; i++)
    {
        good_p[i] = p[i];
    }
    for (int i = 0; i < Y; i++)
    {
        good_q[i] = q[i];
    }
    good_p.push_back(-1e9);
    good_q.push_back(-1e9);
    r.push_back(-1e9);

    ll ans = 0;
    int p_idx = 0, q_idx = 0, r_idx = 0;
    for (int i = 0; i < X + Y; i++)
    {
        if (good_p[p_idx] >= good_q[q_idx] && good_p[p_idx] >= r[r_idx])
        {
            ans += good_p[p_idx];
            p_idx++;
        }
        else if (good_q[q_idx] >= good_p[p_idx] && good_q[q_idx] >= r[r_idx])
        {
            ans += good_q[q_idx];
            q_idx++;
        }
        else
        {
            ans += r[r_idx];
            r_idx++;
        }
    }
    cout << ans << endl;
}