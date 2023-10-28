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

vector<char> ABC = {'A', 'B', 'C'};
string R, C;
int N;
// 各行 / 各列 に A, B, C がちょうど 1 個ずつ含まれる
// i 行目に書かれた文字の中で最も左にある文字は  R の i 文字目と一致する
// i 列目に書かれた文字の中で最も上にある文字は  C の i 文字目と一致する
bool check(vector<string> ans)
{
    for (int i = 0; i < N; i++)
    {
        set<char> s;
        for (int j = 0; j < N; j++)
        {
            if (ans[i][j] != '.')
            {
                if (s.count(ans[i][j]))
                {
                    return false;
                }
                else
                {
                    s.insert(ans[i][j]);
                }
            }
        }
        if (s.size() != 3)
        {
            return false;
        }
    }
    for (int j = 0; j < N; j++)
    {
        set<char> s;
        for (int i = 0; i < N; i++)
        {
            if (ans[i][j] != '.')
            {
                if (s.count(ans[i][j]))
                {
                    return false;
                }
                else
                {
                    s.insert(ans[i][j]);
                }
            }
        }
        if (s.size() != 3)
        {
            return false;
        }
    }
    for (int i = 0; i < N; i++)
    {
        bool r_ok = true;
        for (int j = 0; j < N; j++)
        {
            if (r_ok && ans[i][j] != '.')
            {
                r_ok = false;
                if (ans[i][j] != R[i])
                {
                    return false;
                }
            }
        }
    }
    for (int j = 0; j < N; j++)
    {
        bool c_ok = true;
        for (int i = 0; i < N; i++)
        {
            if (c_ok && ans[i][j] != '.')
            {
                c_ok = false;
                if (ans[i][j] != C[j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

signed main()
{
    cin >> N;
    cin >> R >> C;
    vector<string> ans(N, string(N, '.'));
    // bit全探索
    int bit = 1 << (N * N);
    for (int b = 0; b < bit; b++)
    {
        // いったん置く場所を#にする
        int cnt = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int now_place = i + j * N;
                if (b & (1 << now_place))
                {
                    ans[i][j] = '#';
                    cnt++;
                }
                else
                {
                    ans[i][j] = '.';
                }
            }
        }
        vector<string> origin = ans;
        // ABCを＃に順に置いて全探索
        int loop = pow(3, cnt);
        for (int three_bit = 0; three_bit < loop; three_bit++)
        {
            // 3進数に変換
            int tmp = three_bit;
            vector<int> three;
            while (tmp > 0)
            {
                three.push_back(tmp % 3);
                tmp /= 3;
            }
            while (three.size() < cnt)
            {
                three.push_back(0);
            }
            REVERSE(three);

            // 4進数の各桁について、#の場所にABCを置く
            int idx = 0;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (ans[i][j] == '#')
                    {
                        ans[i][j] = ABC[three[idx++]];
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            if (check(ans))
            {
                cout << "Yes" << endl;
                for (int i = 0; i < N; i++)
                {
                    cout << ans[i] << endl;
                }
                return 0;
            }
            ans = origin;
        }

        // 置く場所を.に戻す
        for (int i = 0; i < N; i++)
        {
            ans[i] = string(N, '.');
        }
    }
    cout << "No" << endl;
}