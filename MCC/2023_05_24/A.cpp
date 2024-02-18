#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << ": {";
        bool not_first = false;
        for (auto j : G[i])
        {
            if (not_first)
            {
                cout << ", ";
            }
            else
            {
                not_first = true;
            }
            cout << j + 1;
        }
        cout << "}\n";
    }
}