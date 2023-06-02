#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &a : A)
        cin >> a;
    for (int i = 0; i < N - 1; i++)
    {
        if (abs(A[i] - A[i + 1]) == 1)
        {
            cout << A[i] << " ";
        }
        else if (A[i] < A[i + 1])
        {
            int j;
            for (j = 0; A[i] + j != A[i + 1]; j++)
            {
                cout << A[i] + j << " ";
            }
        }
        else
        {
            int j;
            for (j = 0; A[i] - j != A[i + 1]; j++)
            {
                cout << A[i] - j << " ";
            }
        }
    }
    cout << A[N - 1] << endl;
}