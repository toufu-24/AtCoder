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
    vector<int> P(N, 0);
    for (int i = 1; i < N; i++)
    {
        cin >> P[i];
        P[i]--;
    }
    set<vector<int>> s;
    s.insert(A);
    vector<int> after;
    after = A;
    vector<int> a_0_senni;
    a_0_senni.push_back(A[0]);
    int cnt = 0;
    for (int loop = 0; true; loop++)
    {
        for (int i = 1; i < N; i++)
        {
            after[P[i]] += after[i];
        }
        if (s.count(after))
        {
            cnt = loop + 1;
            break;
        }
        s.insert(after);
        a_0_senni.push_back(after[0]);
        // cerr << after[0] << endl;
    }
    if (cnt == 0)
    {
        cnt = a_0_senni.size() - 1;
    }
    cerr << cnt << endl;
    modint::set_mod(cnt);
    modint idx = 10;
    idx.pow(100);
    if (a_0_senni[idx.val()] > 0)
    {
        cout << '+' << endl;
    }
    else if (a_0_senni[idx.val()] < 0)
    {
        cout << '-' << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}