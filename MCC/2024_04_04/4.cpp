#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int A, M, L, R;
    cin >> A >> M >> L >> R;
    R -= A;
    L -= A;
    int right = R / M;
    int left = (L - 1) / M;
    int tree = right - left;
    cout << tree << endl;
}
