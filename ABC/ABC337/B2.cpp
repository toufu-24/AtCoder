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

// https://algo-logic.info/run-length/
string encode(const string &str)
{
    int n = (int)str.size();
    string ret = ""; // 答えを格納
    for (int l = 0; l < n;)
    {
        int r = l + 1;
        for (; r < n && str[l] == str[r]; r++)
        {
        };
        ret.push_back(str[l]);
        string num_str = to_string(r - l); // 出現回数
        ret += num_str;
        l = r;
    }
    return ret;
}

int main()
{
    string S;
    cin >> S;
    string T = encode(S);
    for (int i = 0; i < 3; i++)
    {
    }
}