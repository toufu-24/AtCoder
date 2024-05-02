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
    int N, A, B;
    cin >> N >> A >> B;
    modint::set_mod(A + B);
    vector<int> D(N);
    for (int i = 0; i < N; i++)
    {
        cin >> D[i];
    }
    bool ok = false;
    vector<modint> mod;
    for (int i = 0; i < N; i++)
    {
        mod.push_back(A + B);
    }
    sort(all(mod), [&](modint a, modint b)
         { return a.val() < b.val(); });
    if ((mod[N - 1] - mod[0]).val() < A)
    {
        ok = true;
    }
    for (int i = 1; i < N; i++)
    {
        if ((mod[i] + A).val() > mod[i - 1].val() && (mod[i] + A).val() < mod[i].val())
        {
            ok = true;
        }
    }

    if (ok)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
