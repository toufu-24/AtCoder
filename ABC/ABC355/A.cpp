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
    int A, B;
    cin >> A >> B;
    set<int> st = {1, 2, 3};
    st.erase(A);
    st.erase(B);
    if (st.size() == 1)
    {
        cout << *st.begin() << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}
