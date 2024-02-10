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
    int N, Q;
    cin >> N >> Q;
    vector<int> X(N);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i];
    }
    vector<vector<pair<int, int>>> graph(N);
    for (int i = 0; i < N - 1; i++)
    {
        int A, B;
        cin >> A >> B;
        if (A > B)
        {
            swap(A, B);
        }
        // 小 -> 大への有向グラフ
        graph[A - 1].push_back({B - 1, X[B - 1]});
    }

    for (int q = 0; q < Q; q++)
    {
        int V, K;
        cin >> V >> K;
        V--;

        queue<int> que;
        vector<int> num;
        que.push(V);
        num.push_back(X[V]);
        while (!que.empty())
        {
            int v = que.front();
            que.pop();
            for (auto [nv, cost] : graph[v])
            {
                num.push_back(cost);
                que.push(nv);
            }
        }
        sort(num);
        reverse(num);
        cout << num[K - 1] << endl;
    }
}
