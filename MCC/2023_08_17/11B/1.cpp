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
    int N;
    cin >> N;
    vector<string> S(N);
    map<string, int> S_mp;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        S_mp[S[i]]++;
    }
    int max = 0;
    vector<string> ans;
    for (auto x : S_mp)
    {
        if (x.second > max)
        {
            max = x.second;
            ans.clear();
            ans.push_back(x.first);
        }
        else if (x.second == max)
        {
            ans.push_back(x.first);
        }
    }
    sort(ans);
    for (auto out : ans)
    {
        cout << out << endl;
    }
}