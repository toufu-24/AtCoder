#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());
    if (A[0] < A[1] + M)
    {
        M -= A[0] - A[1];
        A[1] = A[0];
    }

    int i;
    for (i = 0; i < M; i += 2)
    {
        A[0]++;
        A[1]++;
    }
    vector<int> A2(N);
    copy(A.begin(), A.end(), A2.begin());
    for (int i = 0; i < N; i++)
    {
        bitset<32> value(A2[i]);
    }
    int count = 0;
    string num = to_string(A2[0] & A2[1]);
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] == 1)
            count++;
    }

    cout << count << endl;
}