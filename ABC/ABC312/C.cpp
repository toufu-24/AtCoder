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
    int N, M;
    cin >> N >> M;
    vector<int> sell(N);
    for (int i = 0; i < N; i++)
    {
        cin >> sell[i];
    }
    sort(sell);
    vector<int> buy(M);
    for (int i = 0; i < M; i++)
    {
        cin >> buy[i];
    }
    sort(buy);
    reverse(buy);

    // にぶたん
    int right = 1e9 + 1;
    int left = -1;
    while (right - left > 1)
    {
        int mid = (left + right) / 2;
        int cnt_sell = 0, cnt_buy = 0;
        for (int i = 0; i < N; i++)
        {
            if (sell[i] <= mid)
            {
                cnt_sell++;
            }
            else if (sell[i] > mid)
            {
                break;
            }
        }
        for (int i = 0; i < M; i++)
        {
            if (buy[i] >= mid)
            {
                cnt_buy++;
            }
            else if (buy[i] < mid)
            {
                break;
            }
        }
        if (cnt_sell >= cnt_buy)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    cout << right << endl;
}