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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        A[i]--;
    }

    vector<pair<int, int>> who_back(N);
    for (int i = 0; i < N; i++)
    {
        who_back[i] = {A[i], i};
    }
    SORT(who_back);
    vector<int> search(N);
    for (int i = 0; i < N; i++)
    {
        search[i] = who_back[i].first;
    }

    vector<int> ans(N);
    ans[0] = who_back[0].second;
    int now = who_back[0].second;
    for (int i = 1; i < N; i++)
    {
        int next_idx = lower_bound(all(search), now) - search.begin();
        int next = who_back[next_idx].second;
        ans[i] = next;
        now = next;
    }

    for (int i = 0; i < N; i++)
    {
        cout << ans[i] + 1 << " ";
    }
}