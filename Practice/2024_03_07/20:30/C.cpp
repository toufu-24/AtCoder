#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    string A, B;
    cin >> A >> B;
    REVERSE(A);
    REVERSE(B);
    int size = min(A.size(), B.size());
    for (int i = size - 1; i >= 0; i--)
    {
        int a = A[i] - '0';
        int b = B[i] - '0';
        if (a + b >= 10)
        {
            cout << "Hard" << endl;
            return 0;
        }
    }
    cout << "Easy" << endl;
}