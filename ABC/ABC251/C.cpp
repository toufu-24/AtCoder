#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    // vector<pair<string, int>> poem(N);
    vector<string> S(N);
    vector<int> T(N);
    vector<bool> isOriginal(N, true);
    set<string> st;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i] >> T[i];
        if (st.count(S[i]))
        {
            isOriginal[i] = false;
        }
        st.insert(S[i]);
    }
    int maxT = 0;
    int maxIndex = 0;
    for (int i = 0; i < N; i++)
    {
        if (isOriginal[i])
        {
            if (T[i] > maxT)
            {
                maxT = T[i];
                maxIndex = i;
            }
        }
    }
    cout << maxIndex + 1 << endl;
}