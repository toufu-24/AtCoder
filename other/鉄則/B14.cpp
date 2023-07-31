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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    vector<int> front(N / 2);
    for (int i = 0; i < N / 2; i++)
    {
        front[i] = A[i];
    }
    ll size = pow(2, N / 2);
    vector<int> front_sum(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < N / 2; j++)
        {
            if (i & (1 << j))
            {
                front_sum[i] += front[j];
            }
        }
    }
    sort(front_sum);
    vector<int> back(N - N / 2);
    for (int i = 0; i < N - N / 2; i++)
    {
        back[i] = A[N - 1 - i];
    }
    ll size2 = pow(2, N - N / 2);
    vector<int> back_sum(size2);
    for (int i = 0; i < size2; i++)
    {
        for (int j = 0; j < N - N / 2; j++)
        {
            if (i & (1 << j))
            {
                back_sum[i] += back[j];
            }
        }
    }
    sort(back_sum);

    for (int i = 0; i < size; i++)
    {
        if (binary_search(all(back_sum), K - front_sum[i]))
        {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
