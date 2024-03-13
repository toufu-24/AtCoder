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
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    for (int i = 0; i < N - 1; i++)
    {
        while (A[i] < A[i + 1])
        {
            cout << A[i] << " ";
            A[i]++;
        }
        while (A[i + 1] < A[i])
        {
            cout << A[i] << " ";
            A[i]--;
        }
    }
    cout << A[N - 1] << endl;
}