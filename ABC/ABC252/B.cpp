#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int max_A = *max_element(all(A));
    set<int> B;
    for (int i = 0; i < K; i++)
    {
        int tmp;
        cin >> tmp;
        B.insert(tmp);
    }
    for (int i = 0; i < N; i++)
    {
        if (A[i] == max_A)
        {
            if (B.count(i + 1))
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}