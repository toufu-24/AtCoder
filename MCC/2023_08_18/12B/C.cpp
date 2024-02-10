#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> ten(N);
    for (int i = 0; i < N; i++)
    {
        cin >> ten[i].first >> ten[i].second;
    }
    sort(ten);
    map<pair<int, int>, vector<pair<int, int>>> xmp;
    map<pair<int, int>, vector<pair<int, int>>> ymp;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (ten[i].first == ten[j].first)
            {
                xmp[ten[i]].push_back(ten[j]);
                xmp[ten[j]].push_back(ten[i]);
            }
            else if (ten[i].second == ten[j].second)
            {
                ymp[ten[i]].push_back(ten[j]);
                ymp[ten[j]].push_back(ten[i]);
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (auto x : xmp[ten[i]])
        {
            for (auto y : ymp[ten[i]])
            {
            }
        }
    }
}