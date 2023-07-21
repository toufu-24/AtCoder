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
    int N, M;
    cin >> N >> M;
    vector<int> P(N);
    vector<int> C(N);
    vector<set<int>> F(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i] >> C[i];
        for (int j = 0; j < C[i]; j++)
        {
            int tmp;
            cin >> tmp;
            F[i].insert(tmp);
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // 値段が安いか
            if (P[i] < P[j])
            {
                continue;
            }
            // 同じものがあるかどうか
            bool same_element = true;
            for (auto k : F[i])
            {
                if (!F[j].count(k))
                {
                    same_element = false;
                    break;
                }
            }
            if (!same_element)
                continue;

            if (F[i] != F[j] || P[i] > P[j])
            {
                cout << "Yes";
                return 0;
            }
        }
    }
    cout << "No";
}