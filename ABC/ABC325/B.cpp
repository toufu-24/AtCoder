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
    vector<pair<int, int>> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i].first >> A[i].second;
    }

    int maximum = 0;
    for (int i = 0; i < 24; i++)
    {
        int cnt = 0;
        for (int j = 0; j < N; j++)
        {
            int time = A[j].second + i;
            time %= 24;
            if (9 <= time && time <= 17)
            {
                cnt += A[j].first;
            }
        }
        maximum = max(maximum, cnt);
    }
    cout << maximum << endl;
}