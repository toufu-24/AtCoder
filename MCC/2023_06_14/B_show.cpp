#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    while (1)
    {
        int N;
        cin >> N;
        if (N == 0)
        {
            break;
        }
        vector<string> S(N);
        int size_max = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> S[i];
        }
        vector<string> code;
        set<string> itti;
        bool itti_falg = false;
        for (int j = 0; j < N; j++)
        {
            // 　空港コードの取得
            string tmp;
            tmp += S[j][0];
            for (int k = 0; k < S[j].size(); k++)
            {
                if (S[j][k] == 'a' || S[j][k] == 'i' || S[j][k] == 'u' || S[j][k] == 'e' || S[j][k] == 'o')
                {
                    if ((k + 1 < S[j].size()))
                    {
                        tmp += S[j][k + 1];
                    }
                }
            }

            if (tmp.size() > size_max)
            {
                size_max = tmp.size();
            }
            code.push_back(tmp);
            if (itti.count(tmp))
            {
                cout << -1 << "\n";
                itti_falg = true;
                break;
            }
            itti.insert(tmp);
        }
        // for (int i = 0; i < N; i++)
        // {
        //     cout << code[i] << endl;
        // }

        if (itti_falg)
        {
            continue;
        }

        for (int i = 0; i < size_max; i++)
        {
            set<char> judge;
            for (int j = 0; j < N; j++)
            {
                if (code[j].size() <= i)
                {
                    continue;
                }
                if (!judge.count(code[j][i]))
                {
                    judge.insert(code[j][i]);
                }
                else
                {
                    break;
                }
            }
            cout << i + 1 << "\n";
            break;
        }
    }
}