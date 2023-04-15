#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;
    vector<int> N(T);
    vector<int> K(T);
    vector<string> S(T);
    for (int i = 0; i < T; i++)
    {
        cin >> N[i] >> K[i] >> S[i];
    }
    vector<string> ans(T);
    for (int i = 0; i < T; i++)
    {
        int cnt_1 = 0;
        int cnt = 0;
        bool flag1 = false;
        bool flag2 = false;
        vector<int> not_zero;
        vector<int> one_place;
        for (int j = 0; j < N[i]; j++)
        {
            if (S[i][j] != '0')
            {
                if (S[i][j] == '1')
                {
                    one_place.push_back(cnt);
                    cnt_1++;
                    if (flag2)
                    {
                        cout << "No" << endl;
                        continue;
                    }
                    flag1 = true;
                }
                cnt++;
            }
            else
            {
                if (flag1)
                {
                    flag2 = true;
                }
                not_zero.push_back(cnt);
                cnt = 0;
            }
        }
        if (S[i][N[i] - 1] != 0)
        {
            not_zero.push_back(cnt);
        }
        if (cnt_1 > K[i])
        {
            cout << "No" << endl;
            continue;
        }
        int not_zero_cnt = 0;
        int length = 0;
        for (int j = 0; j < not_zero.size(); j++)
        {
            if (not_zero[j] >= K[i])
            {
                not_zero_cnt++;
                length = not_zero[j];
            }
        }
        if (not_zero_cnt != 1)
        {
            cout << "No" << endl;
            continue;
        }
        // K以上の長さを持つ列に関してに変化
        if (length == K[i])
        {
            cout << "Yes" << endl;
            continue;
        }
        if (one_place[0] == 1)
        {
            if (one_place[one_place.size() - 1] >= K[i])
            {
                cout << "No" << endl;
                continue;
            }
        }
        if (one_place[one_place.size() - 1] == 1)
        {
            if (one_place[0] < length - K[i])
            {
                cout << "No" << endl;
                continue;
            }
        }
        if (one_place[one_place.size() - 1] - one_place[0] > K[i])
        {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
    }
}