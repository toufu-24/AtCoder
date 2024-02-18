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

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int target;
    cin >> target;
    for (int i = 0; i < (1 << N); i++)
    {
        int sum = 0;
        for (int j = 0; j < N; j++)
        {
            if (i & (1 << j))
            {
                sum += A[j];
            }
        }
        if (sum == target)
        {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}