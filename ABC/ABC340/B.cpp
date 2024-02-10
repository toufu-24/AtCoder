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
    int Q;
    cin >> Q;
    vector<int> A;
    while (Q--)
    {
        int q;
        cin >> q;
        switch (q)
        {
        case 1:
            int x;
            cin >> x;
            A.push_back(x);
            break;
        case 2:
            int k;
            cin >> k;
            cout << A[A.size() - k - 1] << endl;
        default:
            break;
        }
    }
}