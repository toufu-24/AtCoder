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
    int N, M, H, K;
    cin >> N >> M >> H >> K;
    string S;
    cin >> S;
    set<pair<int, int>> item;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        item.insert({a, b});
    }
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    pair<int, int> now = {0, 0};
    for (int i = 0; i < N; i++)
    {
        H--;
        if (H < 0)
        {
            cout << "No" << endl;
            return 0;
        }
        int ope = S[i];
        switch (ope)
        {
        case 'R':
            now.first += dx[0];
            break;
        case 'L':
            now.first += dx[1];
            break;
        case 'U':
            now.second += dy[2];
            break;
        case 'D':
            now.second += dy[3];
            break;
        }
        if (H < K && item.count(now))
        {
            item.erase(now);
            H = K;
        }
        if (H < 0)
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}