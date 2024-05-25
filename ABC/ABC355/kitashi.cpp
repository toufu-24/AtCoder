#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, T;
    cin >> N >> T;
    vector<long long> A(T);
    for (auto &v : A)
        cin >> v;
    vector<long long> h(N), w(N);
    long long count_lurd = 0, count_ldru = 0, h_max = 0, w_max = 0;

    set<long long> lurd, ldru;
    for (int i = 1; i <= N * N; i += N + 1)
        lurd.insert(i);
    for (int i = N; i <= N * N - 1; i += N - 1)
        ldru.insert(i);

    for (int i = 0; i < T; i++)
    {
        h[(A[i] - 1) / N]++;
        h_max = max(h_max, h[(A[i] - 1) / N]);
        w[(A[i] % N)]++;
        w_max = max(w_max, w[(A[i] % N)]);
        if (lurd.count(A[i]))
            count_lurd++;
        if (ldru.count(A[i]))
            count_ldru++;
        if (count_lurd == N || count_ldru == N || h[(A[i] - 1) / N] == N || w[(A[i] % N)] == N)
        {
            cout << i + 1 << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}