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
    vector<int> A(N), C(N);
    vector<tuple<int, int, int>> AC(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i] >> C[i];
        AC[i] = make_tuple(A[i], C[i], i);
    }
    // Aは昇順
    SORT(AC);

    vector<int> remaining;
    int min_cost = LLONG_MAX;

    for (int i = N - 1; i >= 0; i--)
    {
        int a, c, idx;
        tie(a, c, idx) = AC[i];
        if (c < min_cost)
        {
            remaining.push_back(idx);
            min_cost = c;
        }
    }

    SORT(remaining);
    cout << remaining.size() << endl;
    for (int idx : remaining)
    {
        cout << idx + 1 << " ";
    }
    cout << endl;

    return 0;
}