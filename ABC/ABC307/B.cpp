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
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                continue;
            }
            string connect = S[i] + S[j];
            // 回文かどうか判定
            bool is_palindrome = true;
            for (int k = 0; k < connect.size() / 2; k++)
            {
                if (connect[k] != connect[connect.size() - 1 - k])
                {
                    is_palindrome = false;
                    break;
                }
            }
            if (is_palindrome)
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}