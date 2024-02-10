#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int maximum = 0;
    for (int i = 0; i < N; i++)
    {
        int minimum = 1e9;
        for (int j = i; j < N; j++)
        {
            minimum = min(minimum, A[j]);
            maximum = max(minimum * (j - i + 1), maximum);
        }
    }
    cout << maximum;
}