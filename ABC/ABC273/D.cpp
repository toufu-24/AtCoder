#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

struct pair_hash
{
    template <class T1, class T2>
    size_t operator()(pair<T1, T2> const &pair) const
    {
        size_t h1 = hash<T1>()(pair.first);
        size_t h2 = hash<T2>()(pair.second);

        return h1 ^ h2;
    }
};

int main()
{
    int H, W, N;
    pair<int, int> place;
    cin >> H >> W >> place.first >> place.second >> N;
    vector<pair<int, int>> tmp(N);
    for (int i = 0; i < N; i++)
    {
        cin >> tmp[i].first >> tmp[i].second;
    }
    unordered_set<pair<int, int>, pair_hash> wall(all(tmp));
    int Q;
    cin >> Q;
    vector<pair<char, int>> direction(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> direction[i].first >> direction[i].second;
        if (direction[i].first == 'L')
        {
            for (int j = 0; j < direction[i].second; j++)
            {
                place.second--;
                if (place.second < 1 || wall.count(place))
                {
                    place.second++;
                    break;
                }
            }
        }
        else if (direction[i].first == 'R')
        {
            for (int j = 0; j < direction[i].second; j++)
            {
                place.second++;
                if (place.second > W || wall.count(place))
                {
                    place.second--;
                    break;
                }
            }
        }
        else if (direction[i].first == 'U')
        {
            for (int j = 0; j < direction[i].second; j++)
            {
                place.first--;
                if (place.first < 1 || wall.count(place))
                {
                    place.first++;
                    break;
                }
            }
        }
        else if (direction[i].first == 'D')
        {
            for (int j = 0; j < direction[i].second; j++)
            {
                place.first++;
                if (place.first > H || wall.count(place))
                {
                    place.first--;
                    break;
                }
            }
        }
        cout << place.first << " " << place.second << endl;
    }
}