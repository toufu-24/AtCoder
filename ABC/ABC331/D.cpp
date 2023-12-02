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
    int N, Q;
    cin >> N >> Q;
    int one_box_black = 0;
    vector<string> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
        for (int j = 0; j < N; j++)
        {
            if (P[i][j] == 'B')
                one_box_black++;
        }
    }

    while (Q--)
    {
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        int tate = C - A + 1;
        int yoko = D - B + 1;
        cerr << "縦: " << tate << " 横: " << yoko << endl;
        int how_many_boxes = (tate / N) * (yoko / N);
        cerr << "箱数: " << how_many_boxes << endl;
        int ans = one_box_black * how_many_boxes;
        A %= N;
        B %= N;
        C %= N;
        D %= N;
        int cnt = 0;
        for (int i = A; i <= C; i++)
        {
            for (int j = B; j <= D; j++)
            {
                int x = i % N;
                int y = j % N;
                if (P[x][y] == 'B')
                {
                    ans++;
                }
            }
        }
        cerr << "original ans: " << ans << endl;
        if (A == C)
        {
            for (int i = C + 1; i <= C + N; i++)
            {
                for (int j = B; j <= D; j++)
                {
                    int x = i % N;
                    int y = j % N;
                    if (P[x][y] == 'B')
                    {
                        ans += (yoko / N) + 1;
                    }
                }
            }
        }
        cerr << "A == C: " << ans << endl;
        if (B == D)
        {
            D += N;
            for (int i = A; i <= C; i++)
            {
                for (int j = D + 1; j <= D + N; j++)
                {
                    int x = i % N;
                    int y = j % N;
                    if (P[x][y] == 'B')
                    {
                        ans += (tate / N) + 1;
                    }
                }
            }
        }
        cerr << "B == D: " << ans << endl;
        cout << ans << endl;
    }
}