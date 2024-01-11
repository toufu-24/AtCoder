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

#define int ll

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<int> A(K);
    set<int> lost;
    for (int i = 0; i < K; i++)
    {
        cin >> A[i];
        A[i]--;
        lost.insert(A[i]);
    }
    vector<int> renzoku;
    for (int i = 1; i < N; i++)
    {
        if (lost.count(i))
        {
            continue;
        }
        int l = i;
        while (i < N && !lost.count(i))
        {
            i++;
        }
        renzoku.push_back(i - l);
    }

    set<int> all_lost;
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        if (!lost.count(i))
        {
            continue;
        }
        if (all_lost.count(i))
        {
            continue;
        }
        ans++;
        if (lost.count(i + 1))
        {
            all_lost.insert(i + 1);
        }
        lost.insert(i + 1);
    }
    if ((2 * N - K) % 2 == 1)
    {
        ans -= *max_element(all(renzoku)) + 1;
    }
    cout << ans << endl;
}