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
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i] >> Y[i];
    }

    for (int i = 0; i < N; i++)
    {
        int xi = X[i], yi = Y[i];
        int max_dist = 0;
        int max_j = -1;
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                continue;
            }
            int xj = X[j], yj = Y[j];
            int dist = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);
            if (dist > max_dist)
            {
                max_dist = dist;
                max_j = j;
            }
        }
        cout << max_j + 1 << endl;
    }
}
