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
    string S;
    cin >> S;
    vector<int> cnt(26, 0);
    for (int i = 0; i < S.size(); i++)
    {
        cnt[S[i] - 'a']++;
    }

    int max_cnt = 0;
    char max_char = 'a';
    for (int i = 0; i < 26; i++)
    {
        if (cnt[i] > max_cnt)
        {
            max_cnt = cnt[i];
            max_char = 'a' + i;
        }
    }
    cout << max_char << endl;
}