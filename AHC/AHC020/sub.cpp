#include <bits/stdc++.h>
#include <experimental/random>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

bool r_isInside(ll x, ll y, ll broad_x, ll broad_y, ll r)
{
    return (x - broad_x) * (x - broad_x) + (y - broad_y) * (y - broad_y) <= r * r;
}

bool r_isInsideALL(ll x, ll y, vector<pair<ll, ll>> Broadcaster, ll r)
{
    for (auto b : Broadcaster)
    {
        if (r_isInside(x, y, b.first, b.second, r))
        {
            return true;
        }
    }
    return false;
}

bool r_allpoint_isInside(vector<pair<ll, ll>> people, vector<pair<ll, ll>> Broadcaster, ll r)
{
    for (auto p : people)
    {
        if (!r_isInsideALL(p.first, p.second, Broadcaster, r))
        {
            return false;
        }
    }
    return true;
}

bool isInside(ll x, ll y, ll broad_x, ll broad_y, ll r)
{
    return (x - broad_x) * (x - broad_x) + (y - broad_y) * (y - broad_y) <= r * r;
}

bool isInsideALL(ll x, ll y, vector<tuple<ll, ll, int>> Broadcaster)
{
    for (auto b : Broadcaster)
    {
        if (isInside(x, y, get<0>(b), get<1>(b), get<2>(b)))
        {
            return true;
        }
    }
    return false;
}

bool allpoint_isInside(vector<pair<ll, ll>> people, vector<tuple<ll, ll, int>> Broadcaster)
{
    for (auto p : people)
    {
        if (!isInsideALL(p.first, p.second, Broadcaster))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    srand(0);
    long double start = clock();
    ll N, M, K;
    cin >> N >> M >> K;
    vector<pair<ll, ll>> r_Broadcaster(N);
    for (ll i = 0; i < N; i++)
    {
        ll x, y;
        cin >> x >> y;
        r_Broadcaster[i] = make_pair(x, y);
    }
    vector<vector<ll>> graph(N, vector<ll>(N, -1));
    vector<vector<ll>> edge(N);
    vector<vector<ll>> sorted_edge(M, vector<ll>(M, -1));
    for (ll i = 0; i < M; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        graph[u][v] = w;
        graph[v][u] = w;
        edge[u].push_back(i);
        edge[v].push_back(i);
        sorted_edge[i] = {w, i, u, v};
    }
    sort(sorted_edge);
    reverse(sorted_edge);

    vector<pair<ll, ll>> people(K);
    for (ll i = 0; i < K; i++)
    {
        ll x, y;
        cin >> x >> y;
        people[i] = make_pair(x, y);
    }

    int min = 5000;
    long double end = clock();
    while ((end - start) / CLOCKS_PER_SEC < 0.01)
    {
        ll r = experimental::randint(max(0, min - 500), min);
        if (r_allpoint_isInside(people, r_Broadcaster, r))
        {
            min = r;
        }
        end = clock();
    }
    while ((end - start) / CLOCKS_PER_SEC < 0.02)
    {
        ll r = experimental::randint(max(min - 10, 0), min);
        if (r_allpoint_isInside(people, r_Broadcaster, r))
        {
            min = r;
        }
        end = clock();
    }

    vector<tuple<ll, ll, int>> Broadcaster(N);
    for (int i = 0; i < N; i++)
    {
        Broadcaster[i] = make_tuple(r_Broadcaster[i].first, r_Broadcaster[i].second, min);
    }
    while ((end - start) / CLOCKS_PER_SEC < 1.95)
    {
        ll index = rand() % N;
        auto prev_broad = Broadcaster[index];
        if (get<2>(Broadcaster[index]) == 0)
        {
            continue;
        }
        ll r = experimental::randint(max(get<2>(Broadcaster[index]) - 1000, 0), get<2>(Broadcaster[index]));
        Broadcaster[index] = make_tuple(r_Broadcaster[index].first, r_Broadcaster[index].second, r);
        if (!allpoint_isInside(people, Broadcaster))
        {
            Broadcaster[index] = prev_broad;
        }

        end = clock();
    }

    vector<bool> used(M, true);
    // 重みが大きい辺を使えなくする
    for (int i = 0; i < M / 4; i++)
    {
        used[sorted_edge[i][1]] = false;
    }
    // 頂点のstrongが0のとき、確率的にその頂点につながる辺を使えなくする
    for (int i = 0; i < N; i++)
    {
        if (get<2>(Broadcaster[i]) == 0)
        {
            for (auto e : edge[i])
            {
                if (rand() % 6 == 0)
                    used[e] = false;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << get<2>(Broadcaster[i]) << " ";
    }
    cout << endl;
    for (int i = 0; i < M; i++)
    {
        cout << used[i] << " ";
    }
}