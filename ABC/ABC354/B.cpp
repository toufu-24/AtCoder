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
    vector<string> S(N);
    vector<int> C(N);
    vector<pair<string, int>> SC(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i] >> C[i];
        SC[i] = make_pair(S[i], C[i]);
    }
    SORT(SC);
    int sum = reduce(all(C));
    sum %= N;
    cout << SC[sum].first << endl;
}
