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
    vector<pair<int, int>> task(N);
    for (int i = 0; i < N; i++)
    {
        int A, B;
        cin >> A >> B;
        task[i] = {B, A};
    }
    sort(task);
    ll sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += task[i].second;
        if (sum > task[i].first)
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
}