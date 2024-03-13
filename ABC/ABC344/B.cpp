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
    vector<int> A;
    int num = 1;
    while (num != 0)
    {
        cin >> num;
        A.push_back(num);
    }
    REVERSE(A);
    for (int i = 0; i < A.size(); i++)
    {
        cout << A[i] << endl;
    }
}