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
    vector<vector<int>> a(N);
    set<vector<int>> st;
    for (int i = 0; i < N; i++)
    {
        int l;
        cin >> l;
        a[i].resize(l);
        for (int j = 0; j < l; j++)
        {
            cin >> a[i][j];
        }
        st.insert(a[i]);
    }
    cout << st.size() << endl;
}
