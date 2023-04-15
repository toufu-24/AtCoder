#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    priority_queue<int> A;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        A.push(tmp);
    }
    vector<int> three_card(3);
    vector<string> str(3);
    vector<int> one_num(3);
    for (int i = 0; i < 3; i++)
    {
        three_card[i] = A.top();
        A.pop();
        str[i] = to_string(three_card[i]);
        one_num[i] = int(str[i][0] - '0');
    }
    vector<pair<int, int>> card_first;
    for (int i = 0; i < 3; i++)
    {
        card_first.push_back(make_pair(one_num[i], i));
    }

    sort(card_first.begin(), card_first.end());
    reverse(card_first.begin(), card_first.end());
    vector<int> num_line(3);
    for (int i = 0; i < 3; i++)
    {
        num_line[i] = card_first[i].second;
    }

    for (int j = 0; j < 5; j++)
    {
        if (card_first[0].first == card_first[1].first)
        {
            int n = min(str[num_line[0]].size(), str[num_line[1]].size());
            for (int i = 0; i < n; i++)
            {
                if (int(str[num_line[0]][i] - '0') < int(str[num_line[1]][i] - '0'))
                {
                    int tmp = num_line[0];
                    num_line[0] = num_line[1];
                    num_line[1] = tmp;
                    break;
                }
                else if (int(str[num_line[1]][i] - '0') < int(str[num_line[0]][i] - '0'))
                {
                    break;
                }
            }
        }

        if (card_first[1].first == card_first[2].first)
        {
            int n = min(str[num_line[1]].size(), str[num_line[2]].size());
            for (int i = 0; i < n; i++)
            {
                if (int(str[num_line[1]][i] - '0') < int(str[num_line[2]][i] - '0'))
                {
                    int tmp = num_line[1];
                    num_line[1] = num_line[2];
                    num_line[2] = tmp;
                    break;
                }
                else if (int(str[num_line[2]][i] - '0') < int(str[num_line[1]][i] - '0'))
                {
                    break;
                }
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        cout << three_card[num_line[i]];
    }
    cout << endl;
}