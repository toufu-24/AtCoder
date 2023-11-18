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
    int N, Q;
    cin >> N >> Q;
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
        C[i]--;
    }
    vector<bitset<200000>> box(N);
    for (int i = 0; i < N; i++)
    {
        box[i][C[i]] = 1;
    }
    for (int q = 0; q < Q; q++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        box[b] |= box[a];
        box[a].reset();
        cout << box[b].count() << "\n";
    }
}