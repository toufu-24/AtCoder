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
    string S;
    cin >> S;
    reverse(S);
    ll N;
    cin >> N;
    vector<ll> ques_index;
    ll base = 0;
    ll ques = 0;
    for (ll i = 0; i < S.size(); i++)
    {
        if (S[i] == '?')
        {
            ques++;
            ques_index.push_back(i);
        }
        else
        {
            base += (S[i] - '0') * pow(2, i);
        }
    }
    // 2進数生成
    vector<vector<ll>> binary;
    for (ll i = 0; i < pow(2, ques); i++)
    {
        int bina = i;
        vector<ll> tmp;
        for (ll j = 0; j < ques; j++)
        {
            tmp.push_back(bina % 2);
            bina /= 2;
        }
        binary.push_back(tmp);
    }

    // 2進数を10進数に変換
    vector<ll> possible_ans;
    for (int i = 0; i < binary.size(); i++)
    {
        ll tmp = base;
        for (int j = 0; j < binary[i].size(); j++)
        {
            tmp += binary[i][j] * pow(2, S.size() - ques_index[j] - 1);
        }
        possible_ans.push_back(tmp);
    }

    sort(possible_ans);
    auto index = lower_bound(all(possible_ans), N) - possible_ans.begin() - 1;
    if (index < 0)
    {
        cout << -1;
    }
    else
    {
        cout << possible_ans[index] << endl;
    }
}