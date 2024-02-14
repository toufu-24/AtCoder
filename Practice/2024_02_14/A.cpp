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

int main()
{
    int N;
    cin >> N;
    vector<string> S(N);
    vector<string> T(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i] >> T[i];
    }
    set<string> st;
    for (int i = 0; i < N; i++)
    {
        string tmp = S[i] + " " + T[i];
        if (st.count(tmp))
        {
            cout << "Yes" << endl;
            return 0;
        }
        st.insert(tmp);
    }
    cout << "No" << endl;
}