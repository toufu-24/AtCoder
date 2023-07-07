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
    dsu d(N);
    for (int i = 0; i < M; i++)
    {
        int A, B;
        cin >> A >> B;
        d.merge(A - 1, B - 1);
    }
    int K;
    cin >> K;
    vector<pair<int, int>> tyoutenn(K);
    for (int i = 0; i < K; i++)
    {
        int X, Y;
        cin >> X >> Y;
        tyoutenn[i] = make_pair(X - 1, Y - 1);
    }
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        int A, B;
        cin >> A >> B;
        dsu d_copy = d;
        d_copy.merge(A - 1, B - 1);
        bool flag = true;
        for (int i = 0; i < K; i++)
        {
            if (d_copy.same(tyoutenn[i].first, tyoutenn[i].second))
            {
                flag = false;
                break;
            }
        }
        if (flag)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}