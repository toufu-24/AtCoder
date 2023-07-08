#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main() {
    int N1, N2, M;
    cin >> N1 >> N2 >> M;
    vector<vector<int>> G(N1 + N2);
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        G[--a].emplace_back(--b);
        G[b].emplace_back(a);
    }

    vector<int> dist1(N1 + N2, -1);
    queue<int> q;
    dist1[0] = 0;
    q.push(0);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(int nv : G[v]) {
            if(dist1[nv] != -1)
                continue;
            dist1[nv] = dist1[v] + 1;
            q.push(nv);
        }
    }
    int max_dist1 = *max_element(dist1.begin(), dist1.begin() + N1);
    int max_dist1_idx = max_element(dist1.begin(), dist1.begin() + N1) - dist1.begin();

    vector<int> dist2(N1 + N2, -1);
    dist2[N1 + N2 - 1] = 0;
    q.push(N1 + N2 - 1);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(int nv : G[v]) {
            if(dist2[nv] != -1)
                continue;
            dist2[nv] = dist2[v] + 1;
            q.push(nv);
        }
    }
    int max_dist2 = *max_element(dist2.begin() + N1 - 1, dist2.begin() + N1 + N2);
    int max_dist2_idx = max_element(dist2.begin() + N1 - 1, dist2.begin() + N1 + N2) - dist2.begin();

    cout << max_dist1 + max_dist2 + 1 << endl;

    return 0;
}
