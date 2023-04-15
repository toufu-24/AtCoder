#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

void rec(int v, vector<vector<int>> &G, vector<bool> &seen)
{
    // 頂点 v を黒く塗る (= seen[v] を true に変える)
    seen[v] = true;
    // G[v] に含まれる頂点 v2 について、
    for (auto v2 : G[v])
    {
        // v2 がすでに黒く塗られているならば、スキップする
        if (seen[v2])
        {
            continue;
        }
        // v2 始点で深さ優先探索を行う (関数を再帰させる)
        rec(v2, G, seen);
    }
    return;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N, vector<int>(0));
    for (int i = 0; i < M; i++)
    {
        int A, B;
        cin >> A >> B;
        G[A - 1].push_back(B - 1);
        G[B - 1].push_back(A - 1);
    }
    bool ans = true;
    int two = 0;
    int one = 0;
    for (int i = 0; i < N; i++)
    {
        if (G[i].size() == 1)
        {
            one++;
        }
        else if (G[i].size() == 2)
        {
            two++;
        }
        else
        {
            ans = false;
            break;
        }
    }
    if (ans && one == 2 && two == N - 2)
    {
        ans = true;
    }
    else
    {
        ans = false;
    }
    vector<bool> seen(N, false);
    rec(0, G, seen);

    int num = 0; // 答えとなる変数
    // 各頂点 v について、頂点 v が黒く塗られていなければ ans を 1 増やす
    for (int v = 0; v < N; ++v)
    {
        if (seen[v] == false)
        {
            num++;
        }
    }
    if (num != 0)
    {
        ans = false;
    }
    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }

}