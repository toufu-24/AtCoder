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
    int N;
    cin >> N;
    vector<int> sleep;
    vector<int> getUp;
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        if (i % 2 == 0)
        {
            sleep.push_back(a);
        }
        else
        {
            getUp.push_back(a);
        }
    }
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        int l, r;
        cin >> l >> r;
        int left = 0, right = 0;
        left = upper_bound(all(sleep), l) - sleep.begin() - 1;
        right = lower_bound(all(getUp), r) - getUp.begin();
        cout << min(getUp[right], r) - max(sleep[left], l) << endl;
    }
}