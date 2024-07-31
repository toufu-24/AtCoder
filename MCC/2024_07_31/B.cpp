#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main() {
    int N;
    cin >> N;
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < N; j++) {
            A[i][j] = tmp[j] - '0';
        }
    }
    // vector<int> outside;
    // outside.push_back(A[0][1]);
    // for (int i = 0; i < N; i++) {
    //     // outside.push_back({0, i});
    //     outside.push_back(A[0][i]);
    // }
    // for (int i = 1; i < N; i++) {
    //     // outside.push_back({i, 0});
    //     outside.push_back(A[i][0]);
    // }
    // for (int i = 1; i < N; i++) {
    //     // outside.push_back({i, N - 1});
    //     outside.push_back(A[i][N - 1]);
    // }
    // for (int i = 1; i < N; i++) {
    //     // outside.push_back({N - 1, i});
    // }
    int idx = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0) {
                if (j == 0) {
                    cout << A[1][0];
                } else {
                    cout << A[0][j - 1];
                }
            } else if (i == N - 1) {
                if (j == N - 1) {
                    cout << A[N - 2][N - 1];
                } else {
                    cout << A[N - 1][j + 1];
                }
            } else if (j == 0) {
                if (i == N - 1) {
                    cout << A[N - 1][1];
                } else {
                    cout << A[i + 1][0];
                }
            } else if (j == N - 1) {
                if (i == 0) {
                    cout << A[0][N - 2];
                } else {
                    cout << A[i - 1][N - 1];
                }
            } else {
                cout << A[i][j];
            }
        }
        cout << endl;
    }
}
