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
    int N;
    cin >> N;
    vector<int> A(N);
    map<int, int> idx;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int Q;
    cin >> Q;
    while (Q--)
    {
        int q;
        cin >> q;
        int x, y;
        int idx_x;
        switch (q)
        {
        case 1:
            cin >> x >> y;
            idx_x = find(all(A), x) - A.begin();
            A.insert(A.begin() + idx_x + 1, y);
            break;
        case 2:
            cin >> x;
            idx_x = find(all(A), x) - A.begin();
            A.erase(A.begin() + idx_x);
            break;
        }
    }
    for (int i = 0; i < A.size(); i++)
    {
        cout << A[i] << " ";
    }
}