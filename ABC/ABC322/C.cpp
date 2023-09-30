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
    int N, M;
    cin >> N >> M;
    set<int> A;
    for (int i = 0; i < M; i++)
    {
        int in;
        cin >> in;
        in--;
        A.insert(in);
    }
    vector<int> days(N, 0);
    int cnt = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if (A.count(i))
        {
            cnt = 0;
        }
        days[i] = cnt++;
    }
    for (int i = 0; i < N; i++)
    {
        cout << days[i] << endl;
    }
}