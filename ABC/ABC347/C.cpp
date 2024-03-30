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
    vector<int> D(N);
    for (int i = 0; i < N; i++)
    {
        cin >> D[i];
    }
    // mod (A+B) -> A以下なら休日
    bool ok = false;
    vector<int> mod;
    for (int i = 0; i < N; i++)
    {
        mod.push_back(D[i] % (A + B));
    }
    SORT(mod);
    // mod[i]を0日目としたとき，mod[i-1]がA以下なら休日
    if (mod[N - 1] - mod[0] < A)
    {
        ok = true;
    }
    for (int i = 1; i < N; i++)
    {
        if ((mod[i] + A) % (A + B) > mod[i - 1] && (mod[i] + A) % (A + B) <= mod[i])
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
