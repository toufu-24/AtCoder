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
    vector<pair<int, int>> player(N);
    int max_day = 0;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        player[i] = make_pair(a, b);
        max_day = max(max_day, a + b);
    }
    vector<int> imos(max_day + 1, 0);
    for (int i = 0; i < N; i++)
    {
        imos[player[i].first]++;
        imos[player[i].first + player[i].second]--;
    }
    vector<int> people_num(N + 1, 0);
    int now_login = 0;
    for (int i = 1; i <= max_day; i++)
    {
        now_login += imos[i];
        people_num[now_login]++;
    }
    for (int i = 1; i <= N; i++)
    {
        cout << people_num[i] << " ";
    }
}