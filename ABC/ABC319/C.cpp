#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    vector<vector<int>> c(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> c[i][j];
        }
    }
    ld ans = 0;
    ld pass = 8;
    int two_cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        set<int> st;
        for (int j = 0; j < 3; j++)
        {
            st.insert(c[i][j]);
        }
        if (st.size() == 2)
        {
            two_cnt++;
        }
    }
    for (int j = 0; j < 3; j++)
    {
        set<int> st;
        for (int i = 0; i < 3; i++)
        {
            st.insert(c[i][j]);
        }
        if (st.size() == 2)
        {
            two_cnt++;
        }
    }
    set<int> st;
    for (int i = 0; i < 3; i++)
    {
        st.insert(c[i][i]);
    }
    if (st.size() == 2)
    {
        two_cnt++;
    }
    st.clear();
    for (int i = 0; i < 3; i++)
    {
        st.insert(c[i][2 - i]);
    }
    if (st.size() == 2)
    {
        two_cnt++;
    }

    cout << fixed << setprecision(10);
    cout << 1 - two_cnt / pass << endl;
}