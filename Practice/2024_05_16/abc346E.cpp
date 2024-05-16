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

int32_t main()
{
    int H, W, M;
    cin >> H >> W >> M;
    vector<int> T(M), A(M), X(M);
    for (int i = 0; i < M; i++)
    {
        cin >> T[i] >> A[i] >> X[i];
        A[i]--;
    }
    map<int, int> colors;
    int row = W, col = H;
    vector<bool> col_painted(H, false), row_painted(W, false);
    for (int i = M - 1; i >= 0; i--)
    {
        if (T[i] == 1)
        {
            if (col_painted[A[i]])
                continue;
            colors[X[i]] += row;
            col--;
            col_painted[A[i]] = true;
        }
        else
        {
            if (row_painted[A[i]])
                continue;
            colors[X[i]] += col;
            row--;
            row_painted[A[i]] = true;
        }
    }
    colors[0] += row * col;

    vector<int> delete_colors;
    for (const auto &p : colors)
    {
        if (p.second == 0)
            delete_colors.push_back(p.first);
    }
    for (int i = 0; i < delete_colors.size(); i++)
    {
        colors.erase(delete_colors[i]);
    }

    cout << colors.size() << endl;
    for (const auto &p : colors)
    {
        cout << p.first << " " << p.second << endl;
    }
}
