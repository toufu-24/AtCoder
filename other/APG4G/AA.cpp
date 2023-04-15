#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    priority_queue<int> count;
    vector<int> counter(N, 0); //出現回数
    counter.at(0) = 1;
    for (size_t i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        count.push(tmp);
    }
    int tmp1 = count.top();
    count.pop();
    map<int, int> number;
    int j = 0;
    if (N != 1)
    {
        for (size_t i = 0; i < N; i++)
        {
            int tmp2 = count.top();
            count.pop();
            if (tmp1 != tmp2)
            {
                number[counter.at(j)] = tmp1;
                j++;
            }
            counter.at(j)++;
            tmp1 = tmp2;
        }
        sort(counter.begin(), counter.end());
        reverse(counter.begin(), counter.end());
        cout << number.at(counter.at(0)) << " " << counter.at(0) << endl;
    }
    else
        cout << tmp1 << " " << N << endl;
}