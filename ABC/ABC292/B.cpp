#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
using ll = long long;

int main()
{
    ll N, Q;
    cin >> N >> Q;
    vector<int> yellow_cnt(N + 1, 0);
    vector<bool> player(N + 1, false);
    for (int i = 0; i < Q; i++)
    {
        int event, num;
        cin >> event >> num;
        if (event == 1)
        {
            yellow_cnt[num]++;
            if (yellow_cnt[num] == 2)
            {
                player[num] = true;
            }
        }
        else if (event == 2)
        {
            player[num] = true;
        }
        else
        {
            if (player[num])
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }
}