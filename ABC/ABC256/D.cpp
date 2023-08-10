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
    vector<pair<int, int>> kukan(N);
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        kukan[i] = make_pair(a, b);
    }
    sort(kukan);
    vector<pair<int, int>> ans;
    for (int i = 0; i < N; i++)
    {
        int base_i = i;
        int base = kukan[i].second;
        while (base >= kukan[i + 1].first)
        {
            i++;
            if (base < kukan[i].second)
            {
                base = kukan[i].second;
            }
            if (i == N - 1)
            {
                ans.push_back(make_pair(kukan[base_i].first, base));
                goto end;
            }
        }
        if (base <= kukan[i].second)
        {
            ans.push_back(make_pair(kukan[base_i].first, kukan[i].second));
        }
        else
        {
            ans.push_back(make_pair(kukan[base_i].first, base));
        }
    }
end:
    sort(ans);
    for (auto x : ans)
    {
        cout << x.first << " " << x.second << endl;
    }
}