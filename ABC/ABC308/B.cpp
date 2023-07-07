#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N, M;
    cin >> N >> M;
    vector<string> C(N);
    for (int i = 0; i < N; i++)
        cin >> C[i];
    map<string, int> sushi;
    set<string> sushi_set;
    vector<string> sushi_list(M);
    vector<int> sushi_cost(M);
    for (int i = 0; i < M; i++)
    {
        cin >> sushi_list[i];
        sushi_set.insert(sushi_list[i]);
    }
    int base;
    cin >> base;
    for (int i = 0; i < M; i++)
    {
        cin >> sushi_cost[i];
    }

    for (int i = 0; i < M; i++)
    {
        sushi[sushi_list[i]] = sushi_cost[i];
    }

    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        if (sushi_set.count(C[i]))
            sum += sushi[C[i]];
        else
        {
            sum += base;
        }
    }

    cout << sum << endl;
}