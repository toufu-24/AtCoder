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
    vector<vector<int>> graph(N);
    for (int i = 1; i < N; i++)
    {
        int jyoushi;
        cin >> jyoushi;
        graph[jyoushi - 1].push_back(i);
    }

    for (int i = 0; i < N; i++)
    {
        cout << graph[i].size() << endl;
    }
}