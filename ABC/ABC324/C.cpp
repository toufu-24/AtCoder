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

int main()
{
    int N;
    cin >> N;
    string T;
    cin >> T;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    vector<int> ans;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == T)
        {
            ans.push_back(i + 1);
        }
        else
        {
            bool diff = false;
            bool ok = true;
            int t_idx = 0;
            int s_idx = 0;
            switch (int(T.size()) - int(S[i].size()))
            {
            case 1:
                while (t_idx < T.size() && s_idx < S[i].size())
                {
                    if (S[i][s_idx] != T[t_idx])
                    {
                        if (diff)
                        {
                            ok = false;
                            break;
                        }
                        else
                        {
                            diff = true;
                            t_idx++;
                        }
                    }
                    else
                    {
                        t_idx++;
                        s_idx++;
                    }
                }
                if (ok)
                {
                    ans.push_back(i + 1);
                }
                break;
            case 0:
                for (int j = 0; j < T.size(); j++)
                {
                    if (S[i][j] != T[j])
                    {
                        if (diff)
                        {
                            ok = false;
                            break;
                        }
                        else
                        {
                            diff = true;
                        }
                    }
                }
                if (ok)
                {
                    ans.push_back(i + 1);
                }
            case -1:
                while (t_idx < T.size() && s_idx < S[i].size())
                {
                    if (S[i][s_idx] != T[t_idx])
                    {
                        if (diff)
                        {
                            ok = false;
                            break;
                        }
                        else
                        {
                            diff = true;
                            s_idx++;
                        }
                    }
                    else
                    {
                        t_idx++;
                        s_idx++;
                    }
                }
                if (ok)
                {
                    ans.push_back(i + 1);
                }
                break;

            default:
                break;
            }
        }
    }
    SORT(ans);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
}