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
    int N, Q;
    cin >> N >> Q;
    vector<int> T(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> T[i];
    }

    SORT(T);
    T.erase(unique(all(T)), T.end());
    cout << N - T.size() << endl;
}
