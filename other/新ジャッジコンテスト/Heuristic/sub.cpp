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
    int D;
    cin >> D;
    vector<int> c(26);
    for (int i = 0; i < 26; i++)
    {
        cin >> c[i];
    }
    vector<int> last(26, 0);

    for (int i = 0; i < D; i++)
    {
        vector<int> s(vector<int>(26));
        for (int j = 0; j < 26; j++)
        {
            cin >> s[j];
        }
        int out = 0;
        int most_low_index = 0;
        int most_low = -1;
        for (int j = 0; j < 26; j++)
        {
            if (c[j] * (i - last[j]) > most_low)
            {
                most_low = c[j] * (i - last[j]);
                most_low_index = j;
            }
        }
        if (most_low > 1500)
        {
            out = most_low_index;
        }
        else
        {
            out = max_element(all(s)) - s.begin();
        }
        last[out] = i + 1;
        cout << out + 1 << endl;
    }
}