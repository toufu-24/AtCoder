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
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    vector<int> ans(1e5 + 1, 0);
    for (int i = 0; i < N; i++)
    {
        ans[a[i]]++;
        if (a[i] != 0)
            ans[a[i] - 1]++;
        if (a[i] != ans.size() - 1)
            ans[a[i] + 1]++;
    }
    cout << *max_element(all(ans)) << endl;
}