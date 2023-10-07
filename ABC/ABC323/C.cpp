#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    // 値、idx
    vector<pair<int, int>> sorted_A(M);
    for (int i = 0; i < M; i++)
    {
        cin >> A[i];
        sorted_A[i] = {A[i], i};
    }
    SORT(sorted_A);
    REVERSE(sorted_A);
    vector<string> S(N);
    vector<set<int>> AC(N);
    vector<int> point(N, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        for (int j = 0; j < M; j++)
        {
            if (S[i][j] == 'o')
            {
                point[i] += A[j];
                AC[i].insert(j);
            }
        }
        point[i] += i + 1;
    }
    int max_point = *max_element(all(point));
    cerr << "max_point: " << max_point << endl;
    for (int i = 0; i < N; i++)
    {
        int ans = 0;
        int cnt = 0;
        while (point[i] <= max_point)
        {
            int idx = sorted_A[cnt].second;
            if (!AC[i].count(idx))
            {
                point[i] += sorted_A[cnt].first;
                AC[i].insert(idx);
                ans++;
            }
            cnt++;
        }
        cout << ans << endl;
    }
}