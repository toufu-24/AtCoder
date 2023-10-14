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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int n = 0; n < N; n++)
    {
        cin >> A[n];
    }
    for (int i = 0; i < N-1; i++)
    {
        if (A[i] != A[i + 1])
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
}