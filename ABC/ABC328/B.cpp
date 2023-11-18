#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<int> D(N);
    for (int i = 0; i < N; i++)
    {
        cin >> D[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < D[i]; j++)
        {
            string s_i = to_string(i + 1);
            string s_j = to_string(j + 1);
            set<char> s;
            for (int k = 0; k < s_i.size(); k++)
            {
                s.insert(s_i[k]);
            }
            for (int k = 0; k < s_j.size(); k++)
            {
                s.insert(s_j[k]);
            }
            if (s.size() == 1)
            {
                ans++;
            }
        }
    }
    cout << ans << endl;
}