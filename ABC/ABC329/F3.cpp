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
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
        C[i]--;
    }
    map<int, set<int>> ball;
    set<int> box[N];
    for (int i = 0; i < N; i++)
    {
        box[i].insert(C[i]);
        ball[C[i]].insert(i);
    }
    for (int q = 0; q < Q; q++)
    {
        int a, b;
        cin >> a >> b;
        a--; 
        b--;
        box[b].insert(all(box[a]));
        box[a].clear();
        cout << box[b].size() << "\n";
    }
}