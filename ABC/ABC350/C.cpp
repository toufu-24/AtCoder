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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        A[i]--;
    }

    vector<int> idx(N);
    for (int i = 0; i < N; i++)
    {
        idx[A[i]] = i;
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < N; i++)
    {
        if (A[i] == i)
        {
            continue;
        }
        int j = idx[i];
        idx[A[i]] = j;
        idx[i] = i;
        swap(A[i], A[j]);
        ans.push_back({i, j});
    }

    cout << ans.size() << endl;
    for (auto p : ans)
    {
        cout << p.first + 1 << " " << p.second + 1 << endl;
    }
}
